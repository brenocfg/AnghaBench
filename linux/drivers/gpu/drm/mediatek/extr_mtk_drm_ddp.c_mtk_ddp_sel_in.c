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
typedef  enum mtk_ddp_comp_id { ____Placeholder_mtk_ddp_comp_id } mtk_ddp_comp_id ;

/* Variables and functions */
 unsigned int COLOR0_SEL_IN_OVL0 ; 
 unsigned int COLOR1_SEL_IN_OVL1 ; 
 int DDP_COMPONENT_BLS ; 
 int DDP_COMPONENT_COLOR0 ; 
 int DDP_COMPONENT_COLOR1 ; 
 int DDP_COMPONENT_DPI0 ; 
 int DDP_COMPONENT_DPI1 ; 
 int DDP_COMPONENT_DSI0 ; 
 int DDP_COMPONENT_DSI1 ; 
 int DDP_COMPONENT_DSI2 ; 
 int DDP_COMPONENT_DSI3 ; 
 int DDP_COMPONENT_OVL0 ; 
 int DDP_COMPONENT_OVL1 ; 
 int DDP_COMPONENT_RDMA1 ; 
 int DDP_COMPONENT_RDMA2 ; 
 unsigned int DISP_REG_CONFIG_DISP_COLOR0_SEL_IN ; 
 unsigned int DISP_REG_CONFIG_DISP_COLOR1_SEL_IN ; 
 unsigned int DISP_REG_CONFIG_DPI_SEL_IN ; 
 unsigned int DISP_REG_CONFIG_DSIE_SEL_IN ; 
 unsigned int DISP_REG_CONFIG_DSIO_SEL_IN ; 
 unsigned int DISP_REG_CONFIG_DSI_SEL ; 
 unsigned int DPI0_SEL_IN_RDMA1 ; 
 unsigned int DPI0_SEL_IN_RDMA2 ; 
 unsigned int DPI1_SEL_IN_RDMA1 ; 
 unsigned int DPI1_SEL_IN_RDMA2 ; 
 unsigned int DSI0_SEL_IN_RDMA1 ; 
 unsigned int DSI0_SEL_IN_RDMA2 ; 
 unsigned int DSI1_SEL_IN_RDMA1 ; 
 unsigned int DSI1_SEL_IN_RDMA2 ; 
 unsigned int DSI2_SEL_IN_RDMA1 ; 
 unsigned int DSI2_SEL_IN_RDMA2 ; 
 unsigned int DSI3_SEL_IN_RDMA1 ; 
 unsigned int DSI3_SEL_IN_RDMA2 ; 
 unsigned int DSI_SEL_IN_BLS ; 

__attribute__((used)) static unsigned int mtk_ddp_sel_in(enum mtk_ddp_comp_id cur,
				   enum mtk_ddp_comp_id next,
				   unsigned int *addr)
{
	unsigned int value;

	if (cur == DDP_COMPONENT_OVL0 && next == DDP_COMPONENT_COLOR0) {
		*addr = DISP_REG_CONFIG_DISP_COLOR0_SEL_IN;
		value = COLOR0_SEL_IN_OVL0;
	} else if (cur == DDP_COMPONENT_RDMA1 && next == DDP_COMPONENT_DPI0) {
		*addr = DISP_REG_CONFIG_DPI_SEL_IN;
		value = DPI0_SEL_IN_RDMA1;
	} else if (cur == DDP_COMPONENT_RDMA1 && next == DDP_COMPONENT_DPI1) {
		*addr = DISP_REG_CONFIG_DPI_SEL_IN;
		value = DPI1_SEL_IN_RDMA1;
	} else if (cur == DDP_COMPONENT_RDMA1 && next == DDP_COMPONENT_DSI0) {
		*addr = DISP_REG_CONFIG_DSIE_SEL_IN;
		value = DSI0_SEL_IN_RDMA1;
	} else if (cur == DDP_COMPONENT_RDMA1 && next == DDP_COMPONENT_DSI1) {
		*addr = DISP_REG_CONFIG_DSIO_SEL_IN;
		value = DSI1_SEL_IN_RDMA1;
	} else if (cur == DDP_COMPONENT_RDMA1 && next == DDP_COMPONENT_DSI2) {
		*addr = DISP_REG_CONFIG_DSIE_SEL_IN;
		value = DSI2_SEL_IN_RDMA1;
	} else if (cur == DDP_COMPONENT_RDMA1 && next == DDP_COMPONENT_DSI3) {
		*addr = DISP_REG_CONFIG_DSIO_SEL_IN;
		value = DSI3_SEL_IN_RDMA1;
	} else if (cur == DDP_COMPONENT_RDMA2 && next == DDP_COMPONENT_DPI0) {
		*addr = DISP_REG_CONFIG_DPI_SEL_IN;
		value = DPI0_SEL_IN_RDMA2;
	} else if (cur == DDP_COMPONENT_RDMA2 && next == DDP_COMPONENT_DPI1) {
		*addr = DISP_REG_CONFIG_DPI_SEL_IN;
		value = DPI1_SEL_IN_RDMA2;
	} else if (cur == DDP_COMPONENT_RDMA2 && next == DDP_COMPONENT_DSI0) {
		*addr = DISP_REG_CONFIG_DSIE_SEL_IN;
		value = DSI0_SEL_IN_RDMA2;
	} else if (cur == DDP_COMPONENT_RDMA2 && next == DDP_COMPONENT_DSI1) {
		*addr = DISP_REG_CONFIG_DSIO_SEL_IN;
		value = DSI1_SEL_IN_RDMA2;
	} else if (cur == DDP_COMPONENT_RDMA2 && next == DDP_COMPONENT_DSI2) {
		*addr = DISP_REG_CONFIG_DSIE_SEL_IN;
		value = DSI2_SEL_IN_RDMA2;
	} else if (cur == DDP_COMPONENT_RDMA2 && next == DDP_COMPONENT_DSI3) {
		*addr = DISP_REG_CONFIG_DSIE_SEL_IN;
		value = DSI3_SEL_IN_RDMA2;
	} else if (cur == DDP_COMPONENT_OVL1 && next == DDP_COMPONENT_COLOR1) {
		*addr = DISP_REG_CONFIG_DISP_COLOR1_SEL_IN;
		value = COLOR1_SEL_IN_OVL1;
	} else if (cur == DDP_COMPONENT_BLS && next == DDP_COMPONENT_DSI0) {
		*addr = DISP_REG_CONFIG_DSI_SEL;
		value = DSI_SEL_IN_BLS;
	} else {
		value = 0;
	}

	return value;
}