#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev_mbus_code_enum {int pad; int code; scalar_t__ index; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int error; } ;
struct TYPE_9__ {TYPE_4__* ctrl_handler; int /*<<< orphan*/  tvnorms; } ;
struct rvin_dev {int mbus_code; TYPE_3__* parallel; TYPE_4__ ctrl_handler; TYPE_2__ vdev; int /*<<< orphan*/  std; TYPE_1__* info; } ;
struct TYPE_10__ {int source_pad; int sink_pad; struct v4l2_subdev* subdev; } ;
struct TYPE_8__ {scalar_t__ use_mc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOIOCTLCMD ; 
#define  MEDIA_BUS_FMT_RGB888_1X24 132 
#define  MEDIA_BUS_FMT_UYVY10_2X10 131 
#define  MEDIA_BUS_FMT_UYVY8_1X16 130 
#define  MEDIA_BUS_FMT_UYVY8_2X8 129 
#define  MEDIA_BUS_FMT_YUYV8_1X16 128 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  V4L2_CID_ALPHA_COMPONENT ; 
 int /*<<< orphan*/  V4L2_STD_UNKNOWN ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  enum_mbus_code ; 
 int /*<<< orphan*/  g_std ; 
 int /*<<< orphan*/  g_tvnorms ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  rvin_ctrl_ops ; 
 int rvin_find_pad (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int v4l2_ctrl_add_handler (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_4__*) ; 
 int v4l2_ctrl_handler_init (TYPE_4__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  video ; 
 int /*<<< orphan*/  vin_dbg (struct rvin_dev*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vin_err (struct rvin_dev*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rvin_parallel_subdevice_attach(struct rvin_dev *vin,
					  struct v4l2_subdev *subdev)
{
	struct v4l2_subdev_mbus_code_enum code = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	int ret;

	/* Find source and sink pad of remote subdevice */
	ret = rvin_find_pad(subdev, MEDIA_PAD_FL_SOURCE);
	if (ret < 0)
		return ret;
	vin->parallel->source_pad = ret;

	ret = rvin_find_pad(subdev, MEDIA_PAD_FL_SINK);
	vin->parallel->sink_pad = ret < 0 ? 0 : ret;

	if (vin->info->use_mc) {
		vin->parallel->subdev = subdev;
		return 0;
	}

	/* Find compatible subdevices mbus format */
	vin->mbus_code = 0;
	code.index = 0;
	code.pad = vin->parallel->source_pad;
	while (!vin->mbus_code &&
	       !v4l2_subdev_call(subdev, pad, enum_mbus_code, NULL, &code)) {
		code.index++;
		switch (code.code) {
		case MEDIA_BUS_FMT_YUYV8_1X16:
		case MEDIA_BUS_FMT_UYVY8_1X16:
		case MEDIA_BUS_FMT_UYVY8_2X8:
		case MEDIA_BUS_FMT_UYVY10_2X10:
		case MEDIA_BUS_FMT_RGB888_1X24:
			vin->mbus_code = code.code;
			vin_dbg(vin, "Found media bus format for %s: %d\n",
				subdev->name, vin->mbus_code);
			break;
		default:
			break;
		}
	}

	if (!vin->mbus_code) {
		vin_err(vin, "Unsupported media bus format for %s\n",
			subdev->name);
		return -EINVAL;
	}

	/* Read tvnorms */
	ret = v4l2_subdev_call(subdev, video, g_tvnorms, &vin->vdev.tvnorms);
	if (ret < 0 && ret != -ENOIOCTLCMD && ret != -ENODEV)
		return ret;

	/* Read standard */
	vin->std = V4L2_STD_UNKNOWN;
	ret = v4l2_subdev_call(subdev, video, g_std, &vin->std);
	if (ret < 0 && ret != -ENOIOCTLCMD)
		return ret;

	/* Add the controls */
	ret = v4l2_ctrl_handler_init(&vin->ctrl_handler, 16);
	if (ret < 0)
		return ret;

	v4l2_ctrl_new_std(&vin->ctrl_handler, &rvin_ctrl_ops,
			  V4L2_CID_ALPHA_COMPONENT, 0, 255, 1, 255);

	if (vin->ctrl_handler.error) {
		ret = vin->ctrl_handler.error;
		v4l2_ctrl_handler_free(&vin->ctrl_handler);
		return ret;
	}

	ret = v4l2_ctrl_add_handler(&vin->ctrl_handler, subdev->ctrl_handler,
				    NULL, true);
	if (ret < 0) {
		v4l2_ctrl_handler_free(&vin->ctrl_handler);
		return ret;
	}

	vin->vdev.ctrl_handler = &vin->ctrl_handler;

	vin->parallel->subdev = subdev;

	return 0;
}