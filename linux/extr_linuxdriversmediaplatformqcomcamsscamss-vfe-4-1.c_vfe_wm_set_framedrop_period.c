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
typedef  int u8 ;
typedef  int u32 ;
struct vfe_device {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG (int) ; 
 int VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG_FRM_DROP_PER_MASK ; 
 int VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG_FRM_DROP_PER_SHIFT ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void vfe_wm_set_framedrop_period(struct vfe_device *vfe, u8 wm, u8 per)
{
	u32 reg;

	reg = readl_relaxed(vfe->base +
			    VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG(wm));

	reg &= ~(VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG_FRM_DROP_PER_MASK);

	reg |= (per << VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG_FRM_DROP_PER_SHIFT)
		& VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG_FRM_DROP_PER_MASK;

	writel_relaxed(reg,
		       vfe->base + VFE_0_BUS_IMAGE_MASTER_n_WR_ADDR_CFG(wm));
}