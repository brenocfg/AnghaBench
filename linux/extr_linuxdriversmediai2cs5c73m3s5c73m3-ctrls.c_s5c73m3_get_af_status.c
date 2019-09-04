#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u16 ;
struct v4l2_ctrl {int /*<<< orphan*/  val; } ;
struct s5c73m3 {int /*<<< orphan*/  sensor_sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_AF_STATUS ; 
#define  REG_AF_STATUS_FOCUSED 135 
#define  REG_AF_STATUS_FOCUSING 134 
#define  REG_AF_STATUS_INVALID 133 
#define  REG_AF_STATUS_UNFOCUSED 132 
#define  REG_CAF_STATUS_FIND_SEARCH_DIR 131 
#define  REG_CAF_STATUS_FOCUSED 130 
#define  REG_CAF_STATUS_FOCUSING 129 
#define  REG_CAF_STATUS_UNFOCUSED 128 
 int /*<<< orphan*/  V4L2_AUTO_FOCUS_STATUS_BUSY ; 
 int /*<<< orphan*/  V4L2_AUTO_FOCUS_STATUS_FAILED ; 
 int /*<<< orphan*/  V4L2_AUTO_FOCUS_STATUS_REACHED ; 
 int s5c73m3_read (struct s5c73m3*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int s5c73m3_get_af_status(struct s5c73m3 *state, struct v4l2_ctrl *ctrl)
{
	u16 reg = REG_AF_STATUS_UNFOCUSED;

	int ret = s5c73m3_read(state, REG_AF_STATUS, &reg);

	switch (reg) {
	case REG_CAF_STATUS_FIND_SEARCH_DIR:
	case REG_AF_STATUS_FOCUSING:
	case REG_CAF_STATUS_FOCUSING:
		ctrl->val = V4L2_AUTO_FOCUS_STATUS_BUSY;
		break;
	case REG_CAF_STATUS_FOCUSED:
	case REG_AF_STATUS_FOCUSED:
		ctrl->val = V4L2_AUTO_FOCUS_STATUS_REACHED;
		break;
	default:
		v4l2_info(&state->sensor_sd, "Unknown AF status %#x\n", reg);
		/* Fall through */
	case REG_CAF_STATUS_UNFOCUSED:
	case REG_AF_STATUS_UNFOCUSED:
	case REG_AF_STATUS_INVALID:
		ctrl->val = V4L2_AUTO_FOCUS_STATUS_FAILED;
		break;
	}

	return ret;
}