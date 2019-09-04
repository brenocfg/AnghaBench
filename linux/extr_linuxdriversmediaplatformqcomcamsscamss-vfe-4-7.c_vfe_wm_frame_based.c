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
struct vfe_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG (scalar_t__) ; 
 int VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG_FRM_BASED_SHIFT ; 
 int /*<<< orphan*/  vfe_reg_clr (struct vfe_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_reg_set (struct vfe_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vfe_wm_frame_based(struct vfe_device *vfe, u8 wm, u8 enable)
{
	if (enable)
		vfe_reg_set(vfe, VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG(wm),
			1 << VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG_FRM_BASED_SHIFT);
	else
		vfe_reg_clr(vfe, VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG(wm),
			1 << VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG_FRM_BASED_SHIFT);
}