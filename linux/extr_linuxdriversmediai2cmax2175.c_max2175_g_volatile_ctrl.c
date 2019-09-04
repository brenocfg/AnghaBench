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
struct v4l2_ctrl {int id; int val; int /*<<< orphan*/  handler; } ;
struct max2175 {int dummy; } ;

/* Variables and functions */
#define  V4L2_CID_RF_TUNER_IF_GAIN 130 
#define  V4L2_CID_RF_TUNER_LNA_GAIN 129 
#define  V4L2_CID_RF_TUNER_PLL_LOCK 128 
 struct max2175* max2175_from_ctrl_hdl (int /*<<< orphan*/ ) ; 
 int max2175_get_lna_gain (struct max2175*) ; 
 int max2175_read_bits (struct max2175*,int,int,int) ; 

__attribute__((used)) static int max2175_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	struct max2175 *ctx = max2175_from_ctrl_hdl(ctrl->handler);

	switch (ctrl->id) {
	case V4L2_CID_RF_TUNER_LNA_GAIN:
		ctrl->val = max2175_get_lna_gain(ctx);
		break;
	case V4L2_CID_RF_TUNER_IF_GAIN:
		ctrl->val = max2175_read_bits(ctx, 49, 4, 0);
		break;
	case V4L2_CID_RF_TUNER_PLL_LOCK:
		ctrl->val = (max2175_read_bits(ctx, 60, 7, 6) == 3);
		break;
	}

	return 0;
}