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
typedef  scalar_t__ u8 ;
struct isp_device {int dummy; } ;
struct isp_csi2_ctrl_cfg {scalar_t__ if_enable; } ;
struct isp_csi2_device {int /*<<< orphan*/  regs1; struct isp_csi2_ctrl_cfg ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPCSI2_CTRL ; 
 int /*<<< orphan*/  ISPCSI2_CTRL_IF_EN ; 
 int /*<<< orphan*/  isp_reg_clr_set (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void csi2_if_enable(struct isp_device *isp,
			   struct isp_csi2_device *csi2, u8 enable)
{
	struct isp_csi2_ctrl_cfg *currctrl = &csi2->ctrl;

	isp_reg_clr_set(isp, csi2->regs1, ISPCSI2_CTRL, ISPCSI2_CTRL_IF_EN,
			enable ? ISPCSI2_CTRL_IF_EN : 0);

	currctrl->if_enable = enable;
}