#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct v4l2_ctrl_handler {int error; int /*<<< orphan*/ * lock; } ;
struct v4l2_ctrl {int /*<<< orphan*/  flags; } ;
struct ov2685_mode {int hts_def; int width; int vts_def; int height; int exp_def; } ;
struct TYPE_6__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct ov2685 {TYPE_3__ subdev; TYPE_2__* client; int /*<<< orphan*/  test_pattern; void* anal_gain; void* exposure; void* vblank; TYPE_1__* hblank; int /*<<< orphan*/  mutex; struct ov2685_mode* cur_mode; struct v4l2_ctrl_handler ctrl_handler; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int OV2685_BITS_PER_SAMPLE ; 
 int OV2685_EXPOSURE_MIN ; 
 int OV2685_EXPOSURE_STEP ; 
 int OV2685_GAIN_DEFAULT ; 
 int OV2685_GAIN_MAX ; 
 int OV2685_GAIN_MIN ; 
 int OV2685_GAIN_STEP ; 
 int OV2685_LANES ; 
 int OV2685_VTS_MAX ; 
 int /*<<< orphan*/  V4L2_CID_ANALOGUE_GAIN ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE ; 
 int /*<<< orphan*/  V4L2_CID_HBLANK ; 
 int /*<<< orphan*/  V4L2_CID_LINK_FREQ ; 
 int /*<<< orphan*/  V4L2_CID_PIXEL_RATE ; 
 int /*<<< orphan*/  V4L2_CID_TEST_PATTERN ; 
 int /*<<< orphan*/  V4L2_CID_VBLANK ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_READ_ONLY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int* link_freq_menu_items ; 
 int /*<<< orphan*/  ov2685_ctrl_ops ; 
 int /*<<< orphan*/  ov2685_test_pattern_menu ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (struct v4l2_ctrl_handler*) ; 
 int v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 struct v4l2_ctrl* v4l2_ctrl_new_int_menu (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 void* v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu_items (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov2685_initialize_controls(struct ov2685 *ov2685)
{
	const struct ov2685_mode *mode;
	struct v4l2_ctrl_handler *handler;
	struct v4l2_ctrl *ctrl;
	u64 exposure_max;
	u32 pixel_rate, h_blank;
	int ret;

	handler = &ov2685->ctrl_handler;
	mode = ov2685->cur_mode;
	ret = v4l2_ctrl_handler_init(handler, 8);
	if (ret)
		return ret;
	handler->lock = &ov2685->mutex;

	ctrl = v4l2_ctrl_new_int_menu(handler, NULL, V4L2_CID_LINK_FREQ,
				      0, 0, link_freq_menu_items);
	if (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	pixel_rate = (link_freq_menu_items[0] * 2 * OV2685_LANES) /
		     OV2685_BITS_PER_SAMPLE;
	v4l2_ctrl_new_std(handler, NULL, V4L2_CID_PIXEL_RATE,
			  0, pixel_rate, 1, pixel_rate);

	h_blank = mode->hts_def - mode->width;
	ov2685->hblank = v4l2_ctrl_new_std(handler, NULL, V4L2_CID_HBLANK,
				h_blank, h_blank, 1, h_blank);
	if (ov2685->hblank)
		ov2685->hblank->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	ov2685->vblank = v4l2_ctrl_new_std(handler, &ov2685_ctrl_ops,
				V4L2_CID_VBLANK, mode->vts_def - mode->height,
				OV2685_VTS_MAX - mode->height, 1,
				mode->vts_def - mode->height);

	exposure_max = mode->vts_def - 4;
	ov2685->exposure = v4l2_ctrl_new_std(handler, &ov2685_ctrl_ops,
				V4L2_CID_EXPOSURE, OV2685_EXPOSURE_MIN,
				exposure_max, OV2685_EXPOSURE_STEP,
				mode->exp_def);

	ov2685->anal_gain = v4l2_ctrl_new_std(handler, &ov2685_ctrl_ops,
				V4L2_CID_ANALOGUE_GAIN, OV2685_GAIN_MIN,
				OV2685_GAIN_MAX, OV2685_GAIN_STEP,
				OV2685_GAIN_DEFAULT);

	ov2685->test_pattern = v4l2_ctrl_new_std_menu_items(handler,
				&ov2685_ctrl_ops, V4L2_CID_TEST_PATTERN,
				ARRAY_SIZE(ov2685_test_pattern_menu) - 1,
				0, 0, ov2685_test_pattern_menu);

	if (handler->error) {
		ret = handler->error;
		dev_err(&ov2685->client->dev,
			"Failed to init controls(%d)\n", ret);
		goto err_free_handler;
	}

	ov2685->subdev.ctrl_handler = handler;

	return 0;

err_free_handler:
	v4l2_ctrl_handler_free(handler);

	return ret;
}