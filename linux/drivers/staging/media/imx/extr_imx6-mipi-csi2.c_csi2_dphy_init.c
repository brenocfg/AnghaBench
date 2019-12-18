#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_ctrl {int* qmenu_int; size_t val; } ;
struct csi2_dev {TYPE_1__* src_sd; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI2_DEFAULT_MAX_MBPS ; 
 int /*<<< orphan*/  DIV_ROUND_UP_ULL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USEC_PER_SEC ; 
 int /*<<< orphan*/  V4L2_CID_LINK_FREQ ; 
 int /*<<< orphan*/  dw_mipi_csi2_phy_write (struct csi2_dev*,int,int) ; 
 int max_mbps_to_hsfreqrange_sel (int /*<<< orphan*/ ) ; 
 struct v4l2_ctrl* v4l2_ctrl_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int csi2_dphy_init(struct csi2_dev *csi2)
{
	struct v4l2_ctrl *ctrl;
	u32 mbps_per_lane;
	int sel;

	ctrl = v4l2_ctrl_find(csi2->src_sd->ctrl_handler,
			      V4L2_CID_LINK_FREQ);
	if (!ctrl)
		mbps_per_lane = CSI2_DEFAULT_MAX_MBPS;
	else
		mbps_per_lane = DIV_ROUND_UP_ULL(2 * ctrl->qmenu_int[ctrl->val],
						 USEC_PER_SEC);

	sel = max_mbps_to_hsfreqrange_sel(mbps_per_lane);
	if (sel < 0)
		return sel;

	dw_mipi_csi2_phy_write(csi2, 0x44, sel);

	return 0;
}