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
 int VBIF_IN_RD_LIM_CONF0 ; 
 int VBIF_IN_WR_LIM_CONF0 ; 

__attribute__((used)) static void dpu_hw_set_limit_conf(struct dpu_hw_vbif *vbif,
		u32 xin_id, bool rd, u32 limit)
{
	struct dpu_hw_blk_reg_map *c = &vbif->hw;
	u32 reg_val;
	u32 reg_off;
	u32 bit_off;

	if (rd)
		reg_off = VBIF_IN_RD_LIM_CONF0;
	else
		reg_off = VBIF_IN_WR_LIM_CONF0;

	reg_off += (xin_id / 4) * 4;
	bit_off = (xin_id % 4) * 8;
	reg_val = DPU_REG_READ(c, reg_off);
	reg_val &= ~(0xFF << bit_off);
	reg_val |= (limit) << bit_off;
	DPU_REG_WRITE(c, reg_off, reg_val);
}