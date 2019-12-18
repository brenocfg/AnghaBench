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
struct vfe_device {int dummy; } ;
typedef  enum vfe_line_id { ____Placeholder_vfe_line_id } vfe_line_id ;

/* Variables and functions */
 int /*<<< orphan*/  VFE_0_BUS_XBAR_CFG_x (int) ; 
 int VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_SHIFT ; 
 int VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_VAL_RDI0 ; 
 int VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_VAL_RDI1 ; 
 int VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_VAL_RDI2 ; 
 int /*<<< orphan*/  VFE_0_RDI_CFG_x (int) ; 
 int VFE_0_RDI_CFG_x_RDI_EN_BIT ; 
#define  VFE_LINE_RDI0 130 
#define  VFE_LINE_RDI1 129 
#define  VFE_LINE_RDI2 128 
 int /*<<< orphan*/  vfe_reg_clr (struct vfe_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vfe_bus_disconnect_wm_from_rdi(struct vfe_device *vfe, u8 wm,
					   enum vfe_line_id id)
{
	u32 reg;

	reg = VFE_0_RDI_CFG_x_RDI_EN_BIT;
	vfe_reg_clr(vfe, VFE_0_RDI_CFG_x(id), reg);

	switch (id) {
	case VFE_LINE_RDI0:
	default:
		reg = VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_VAL_RDI0 <<
		      VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_SHIFT;
		break;
	case VFE_LINE_RDI1:
		reg = VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_VAL_RDI1 <<
		      VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_SHIFT;
		break;
	case VFE_LINE_RDI2:
		reg = VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_VAL_RDI2 <<
		      VFE_0_BUS_XBAR_CFG_x_M_SINGLE_STREAM_SEL_SHIFT;
		break;
	}

	if (wm % 2 == 1)
		reg <<= 16;

	vfe_reg_clr(vfe, VFE_0_BUS_XBAR_CFG_x(wm), reg);
}