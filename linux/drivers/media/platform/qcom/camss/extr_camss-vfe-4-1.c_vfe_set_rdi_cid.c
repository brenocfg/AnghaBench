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
struct vfe_device {int dummy; } ;
typedef  enum vfe_line_id { ____Placeholder_vfe_line_id } vfe_line_id ;

/* Variables and functions */
 int /*<<< orphan*/  VFE_0_RDI_CFG_x (int) ; 
 int /*<<< orphan*/  VFE_0_RDI_CFG_x_RDI_M0_SEL_MASK ; 
 int VFE_0_RDI_CFG_x_RDI_M0_SEL_SHIFT ; 
 int /*<<< orphan*/  vfe_reg_clr (struct vfe_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfe_reg_set (struct vfe_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vfe_set_rdi_cid(struct vfe_device *vfe, enum vfe_line_id id, u8 cid)
{
	vfe_reg_clr(vfe, VFE_0_RDI_CFG_x(id),
		    VFE_0_RDI_CFG_x_RDI_M0_SEL_MASK);

	vfe_reg_set(vfe, VFE_0_RDI_CFG_x(id),
		    cid << VFE_0_RDI_CFG_x_RDI_M0_SEL_SHIFT);
}