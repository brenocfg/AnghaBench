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
 int DDP_COMPONENT_COLOR0 ; 
 int DDP_COMPONENT_COLOR1 ; 
 int DDP_COMPONENT_DPI0 ; 
 int DDP_COMPONENT_DPI1 ; 
 int DDP_COMPONENT_DSI0 ; 
 int DDP_COMPONENT_DSI1 ; 
 int DDP_COMPONENT_DSI2 ; 
 int DDP_COMPONENT_DSI3 ; 
 int DDP_COMPONENT_GAMMA ; 
 int DDP_COMPONENT_OD0 ; 
 int DDP_COMPONENT_OD1 ; 
 int DDP_COMPONENT_OVL0 ; 
 int DDP_COMPONENT_OVL1 ; 
 int DDP_COMPONENT_RDMA0 ; 
 int DDP_COMPONENT_RDMA1 ; 
 int DDP_COMPONENT_RDMA2 ; 
 int DDP_COMPONENT_UFOE ; 
 unsigned int DISP_REG_CONFIG_DISP_GAMMA_MOUT_EN ; 
 unsigned int DISP_REG_CONFIG_DISP_OD_MOUT_EN ; 
 unsigned int DISP_REG_CONFIG_DISP_OVL0_MOUT_EN ; 
 unsigned int DISP_REG_CONFIG_DISP_OVL1_MOUT_EN ; 
 unsigned int DISP_REG_CONFIG_DISP_OVL_MOUT_EN ; 
 unsigned int DISP_REG_CONFIG_DISP_RDMA0_SOUT_EN ; 
 unsigned int DISP_REG_CONFIG_DISP_RDMA1_SOUT_EN ; 
 unsigned int DISP_REG_CONFIG_DISP_RDMA2_SOUT ; 
 unsigned int DISP_REG_CONFIG_DISP_UFOE_MOUT_EN ; 
 unsigned int GAMMA_MOUT_EN_RDMA1 ; 
 unsigned int OD1_MOUT_EN_RDMA1 ; 
 unsigned int OD_MOUT_EN_RDMA0 ; 
 unsigned int OVL0_MOUT_EN_COLOR0 ; 
 unsigned int OVL1_MOUT_EN_COLOR1 ; 
 unsigned int OVL_MOUT_EN_RDMA ; 
 unsigned int RDMA0_SOUT_DPI0 ; 
 unsigned int RDMA0_SOUT_DPI1 ; 
 unsigned int RDMA0_SOUT_DSI1 ; 
 unsigned int RDMA0_SOUT_DSI2 ; 
 unsigned int RDMA0_SOUT_DSI3 ; 
 unsigned int RDMA1_SOUT_DPI0 ; 
 unsigned int RDMA1_SOUT_DPI1 ; 
 unsigned int RDMA1_SOUT_DSI1 ; 
 unsigned int RDMA1_SOUT_DSI2 ; 
 unsigned int RDMA1_SOUT_DSI3 ; 
 unsigned int RDMA2_SOUT_DPI0 ; 
 unsigned int RDMA2_SOUT_DPI1 ; 
 unsigned int RDMA2_SOUT_DSI1 ; 
 unsigned int RDMA2_SOUT_DSI2 ; 
 unsigned int RDMA2_SOUT_DSI3 ; 
 unsigned int UFOE_MOUT_EN_DSI0 ; 

__attribute__((used)) static unsigned int mtk_ddp_mout_en(enum mtk_ddp_comp_id cur,
				    enum mtk_ddp_comp_id next,
				    unsigned int *addr)
{
	unsigned int value;

	if (cur == DDP_COMPONENT_OVL0 && next == DDP_COMPONENT_COLOR0) {
		*addr = DISP_REG_CONFIG_DISP_OVL0_MOUT_EN;
		value = OVL0_MOUT_EN_COLOR0;
	} else if (cur == DDP_COMPONENT_OVL0 && next == DDP_COMPONENT_RDMA0) {
		*addr = DISP_REG_CONFIG_DISP_OVL_MOUT_EN;
		value = OVL_MOUT_EN_RDMA;
	} else if (cur == DDP_COMPONENT_OD0 && next == DDP_COMPONENT_RDMA0) {
		*addr = DISP_REG_CONFIG_DISP_OD_MOUT_EN;
		value = OD_MOUT_EN_RDMA0;
	} else if (cur == DDP_COMPONENT_UFOE && next == DDP_COMPONENT_DSI0) {
		*addr = DISP_REG_CONFIG_DISP_UFOE_MOUT_EN;
		value = UFOE_MOUT_EN_DSI0;
	} else if (cur == DDP_COMPONENT_OVL1 && next == DDP_COMPONENT_COLOR1) {
		*addr = DISP_REG_CONFIG_DISP_OVL1_MOUT_EN;
		value = OVL1_MOUT_EN_COLOR1;
	} else if (cur == DDP_COMPONENT_GAMMA && next == DDP_COMPONENT_RDMA1) {
		*addr = DISP_REG_CONFIG_DISP_GAMMA_MOUT_EN;
		value = GAMMA_MOUT_EN_RDMA1;
	} else if (cur == DDP_COMPONENT_OD1 && next == DDP_COMPONENT_RDMA1) {
		*addr = DISP_REG_CONFIG_DISP_OD_MOUT_EN;
		value = OD1_MOUT_EN_RDMA1;
	} else if (cur == DDP_COMPONENT_RDMA0 && next == DDP_COMPONENT_DPI0) {
		*addr = DISP_REG_CONFIG_DISP_RDMA0_SOUT_EN;
		value = RDMA0_SOUT_DPI0;
	} else if (cur == DDP_COMPONENT_RDMA0 && next == DDP_COMPONENT_DPI1) {
		*addr = DISP_REG_CONFIG_DISP_RDMA0_SOUT_EN;
		value = RDMA0_SOUT_DPI1;
	} else if (cur == DDP_COMPONENT_RDMA0 && next == DDP_COMPONENT_DSI1) {
		*addr = DISP_REG_CONFIG_DISP_RDMA0_SOUT_EN;
		value = RDMA0_SOUT_DSI1;
	} else if (cur == DDP_COMPONENT_RDMA0 && next == DDP_COMPONENT_DSI2) {
		*addr = DISP_REG_CONFIG_DISP_RDMA0_SOUT_EN;
		value = RDMA0_SOUT_DSI2;
	} else if (cur == DDP_COMPONENT_RDMA0 && next == DDP_COMPONENT_DSI3) {
		*addr = DISP_REG_CONFIG_DISP_RDMA0_SOUT_EN;
		value = RDMA0_SOUT_DSI3;
	} else if (cur == DDP_COMPONENT_RDMA1 && next == DDP_COMPONENT_DSI1) {
		*addr = DISP_REG_CONFIG_DISP_RDMA1_SOUT_EN;
		value = RDMA1_SOUT_DSI1;
	} else if (cur == DDP_COMPONENT_RDMA1 && next == DDP_COMPONENT_DSI2) {
		*addr = DISP_REG_CONFIG_DISP_RDMA1_SOUT_EN;
		value = RDMA1_SOUT_DSI2;
	} else if (cur == DDP_COMPONENT_RDMA1 && next == DDP_COMPONENT_DSI3) {
		*addr = DISP_REG_CONFIG_DISP_RDMA1_SOUT_EN;
		value = RDMA1_SOUT_DSI3;
	} else if (cur == DDP_COMPONENT_RDMA1 && next == DDP_COMPONENT_DPI0) {
		*addr = DISP_REG_CONFIG_DISP_RDMA1_SOUT_EN;
		value = RDMA1_SOUT_DPI0;
	} else if (cur == DDP_COMPONENT_RDMA1 && next == DDP_COMPONENT_DPI1) {
		*addr = DISP_REG_CONFIG_DISP_RDMA1_SOUT_EN;
		value = RDMA1_SOUT_DPI1;
	} else if (cur == DDP_COMPONENT_RDMA2 && next == DDP_COMPONENT_DPI0) {
		*addr = DISP_REG_CONFIG_DISP_RDMA2_SOUT;
		value = RDMA2_SOUT_DPI0;
	} else if (cur == DDP_COMPONENT_RDMA2 && next == DDP_COMPONENT_DPI1) {
		*addr = DISP_REG_CONFIG_DISP_RDMA2_SOUT;
		value = RDMA2_SOUT_DPI1;
	} else if (cur == DDP_COMPONENT_RDMA2 && next == DDP_COMPONENT_DSI1) {
		*addr = DISP_REG_CONFIG_DISP_RDMA2_SOUT;
		value = RDMA2_SOUT_DSI1;
	} else if (cur == DDP_COMPONENT_RDMA2 && next == DDP_COMPONENT_DSI2) {
		*addr = DISP_REG_CONFIG_DISP_RDMA2_SOUT;
		value = RDMA2_SOUT_DSI2;
	} else if (cur == DDP_COMPONENT_RDMA2 && next == DDP_COMPONENT_DSI3) {
		*addr = DISP_REG_CONFIG_DISP_RDMA2_SOUT;
		value = RDMA2_SOUT_DSI3;
	} else {
		value = 0;
	}

	return value;
}