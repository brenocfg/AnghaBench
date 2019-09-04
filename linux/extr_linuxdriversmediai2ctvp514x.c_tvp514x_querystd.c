#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v4l2_std_id ;
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct tvp514x_decoder {int input; TYPE_2__* std_list; int /*<<< orphan*/  streaming; } ;
typedef  enum tvp514x_std { ____Placeholder_tvp514x_std } tvp514x_std ;
typedef  enum tvp514x_input { ____Placeholder_tvp514x_input } tvp514x_input ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__ standard; } ;

/* Variables and functions */
 int EINVAL ; 
#define  INPUT_CVBS_VI1A 149 
#define  INPUT_CVBS_VI1B 148 
#define  INPUT_CVBS_VI1C 147 
#define  INPUT_CVBS_VI2A 146 
#define  INPUT_CVBS_VI2B 145 
#define  INPUT_CVBS_VI2C 144 
#define  INPUT_CVBS_VI3A 143 
#define  INPUT_CVBS_VI3B 142 
#define  INPUT_CVBS_VI3C 141 
#define  INPUT_CVBS_VI4A 140 
#define  INPUT_SVIDEO_VI2A_VI1A 139 
#define  INPUT_SVIDEO_VI2A_VI3A 138 
#define  INPUT_SVIDEO_VI2B_VI1B 137 
#define  INPUT_SVIDEO_VI2B_VI3B 136 
#define  INPUT_SVIDEO_VI2C_VI1C 135 
#define  INPUT_SVIDEO_VI2C_VI3C 134 
#define  INPUT_SVIDEO_VI4A_VI1A 133 
#define  INPUT_SVIDEO_VI4A_VI1B 132 
#define  INPUT_SVIDEO_VI4A_VI1C 131 
#define  INPUT_SVIDEO_VI4A_VI3A 130 
#define  INPUT_SVIDEO_VI4A_VI3B 129 
#define  INPUT_SVIDEO_VI4A_VI3C 128 
 int /*<<< orphan*/  LOCK_RETRY_DELAY ; 
 int /*<<< orphan*/  REG_STATUS1 ; 
 int STATUS_CLR_SUBCAR_LOCK_BIT ; 
 int STATUS_HORZ_SYNC_LOCK_BIT ; 
 int STATUS_VIRT_SYNC_LOCK_BIT ; 
 int STD_INVALID ; 
 int /*<<< orphan*/  V4L2_STD_UNKNOWN ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 struct tvp514x_decoder* to_decoder (struct v4l2_subdev*) ; 
 int tvp514x_query_current_std (struct v4l2_subdev*) ; 
 int tvp514x_read_reg (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvp514x_s_stream (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tvp514x_querystd(struct v4l2_subdev *sd, v4l2_std_id *std_id)
{
	struct tvp514x_decoder *decoder = to_decoder(sd);
	enum tvp514x_std current_std;
	enum tvp514x_input input_sel;
	u8 sync_lock_status, lock_mask;

	if (std_id == NULL)
		return -EINVAL;

	/* To query the standard the TVP514x must power on the ADCs. */
	if (!decoder->streaming) {
		tvp514x_s_stream(sd, 1);
		msleep(LOCK_RETRY_DELAY);
	}

	/* query the current standard */
	current_std = tvp514x_query_current_std(sd);
	if (current_std == STD_INVALID) {
		*std_id = V4L2_STD_UNKNOWN;
		return 0;
	}

	input_sel = decoder->input;

	switch (input_sel) {
	case INPUT_CVBS_VI1A:
	case INPUT_CVBS_VI1B:
	case INPUT_CVBS_VI1C:
	case INPUT_CVBS_VI2A:
	case INPUT_CVBS_VI2B:
	case INPUT_CVBS_VI2C:
	case INPUT_CVBS_VI3A:
	case INPUT_CVBS_VI3B:
	case INPUT_CVBS_VI3C:
	case INPUT_CVBS_VI4A:
		lock_mask = STATUS_CLR_SUBCAR_LOCK_BIT |
			STATUS_HORZ_SYNC_LOCK_BIT |
			STATUS_VIRT_SYNC_LOCK_BIT;
		break;

	case INPUT_SVIDEO_VI2A_VI1A:
	case INPUT_SVIDEO_VI2B_VI1B:
	case INPUT_SVIDEO_VI2C_VI1C:
	case INPUT_SVIDEO_VI2A_VI3A:
	case INPUT_SVIDEO_VI2B_VI3B:
	case INPUT_SVIDEO_VI2C_VI3C:
	case INPUT_SVIDEO_VI4A_VI1A:
	case INPUT_SVIDEO_VI4A_VI1B:
	case INPUT_SVIDEO_VI4A_VI1C:
	case INPUT_SVIDEO_VI4A_VI3A:
	case INPUT_SVIDEO_VI4A_VI3B:
	case INPUT_SVIDEO_VI4A_VI3C:
		lock_mask = STATUS_HORZ_SYNC_LOCK_BIT |
			STATUS_VIRT_SYNC_LOCK_BIT;
		break;
		/*Need to add other interfaces*/
	default:
		return -EINVAL;
	}
	/* check whether signal is locked */
	sync_lock_status = tvp514x_read_reg(sd, REG_STATUS1);
	if (lock_mask != (sync_lock_status & lock_mask)) {
		*std_id = V4L2_STD_UNKNOWN;
		return 0;	/* No input detected */
	}

	*std_id &= decoder->std_list[current_std].standard.id;

	v4l2_dbg(1, debug, sd, "Current STD: %s\n",
			decoder->std_list[current_std].standard.name);
	return 0;
}