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
typedef  int u32 ;
struct dpu_hw_blk_reg_map {int dummy; } ;
struct dpu_hw_vbif {struct dpu_hw_blk_reg_map hw; } ;

/* Variables and functions */
 int DPU_REG_READ (struct dpu_hw_blk_reg_map*,int) ; 
 int /*<<< orphan*/  DPU_REG_WRITE (struct dpu_hw_blk_reg_map*,int,int) ; 
 int MAX_XIN_COUNT ; 
 int VBIF_OUT_AXI_AMEMTYPE_CONF0 ; 
 int VBIF_OUT_AXI_AMEMTYPE_CONF1 ; 

__attribute__((used)) static void dpu_hw_set_mem_type(struct dpu_hw_vbif *vbif,
		u32 xin_id, u32 value)
{
	struct dpu_hw_blk_reg_map *c;
	u32 reg_off;
	u32 bit_off;
	u32 reg_val;

	/*
	 * Assume 4 bits per bit field, 8 fields per 32-bit register so
	 * 16 bit fields maximum across two registers
	 */
	if (!vbif || xin_id >= MAX_XIN_COUNT || xin_id >= 16)
		return;

	c = &vbif->hw;

	if (xin_id >= 8) {
		xin_id -= 8;
		reg_off = VBIF_OUT_AXI_AMEMTYPE_CONF1;
	} else {
		reg_off = VBIF_OUT_AXI_AMEMTYPE_CONF0;
	}
	bit_off = (xin_id & 0x7) * 4;
	reg_val = DPU_REG_READ(c, reg_off);
	reg_val &= ~(0x7 << bit_off);
	reg_val |= (value & 0x7) << bit_off;
	DPU_REG_WRITE(c, reg_off, reg_val);
}