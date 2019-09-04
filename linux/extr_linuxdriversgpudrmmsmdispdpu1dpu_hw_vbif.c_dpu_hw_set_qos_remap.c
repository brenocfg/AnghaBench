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
 int DPU_REG_READ (struct dpu_hw_blk_reg_map*,scalar_t__) ; 
 int /*<<< orphan*/  DPU_REG_WRITE (struct dpu_hw_blk_reg_map*,scalar_t__,int) ; 
 scalar_t__ VBIF_XINL_QOS_LVL_REMAP_000 ; 
 scalar_t__ VBIF_XINL_QOS_RP_REMAP_000 ; 

__attribute__((used)) static void dpu_hw_set_qos_remap(struct dpu_hw_vbif *vbif,
		u32 xin_id, u32 level, u32 remap_level)
{
	struct dpu_hw_blk_reg_map *c;
	u32 reg_val, reg_val_lvl, mask, reg_high, reg_shift;

	if (!vbif)
		return;

	c = &vbif->hw;

	reg_high = ((xin_id & 0x8) >> 3) * 4 + (level * 8);
	reg_shift = (xin_id & 0x7) * 4;

	reg_val = DPU_REG_READ(c, VBIF_XINL_QOS_RP_REMAP_000 + reg_high);
	reg_val_lvl = DPU_REG_READ(c, VBIF_XINL_QOS_LVL_REMAP_000 + reg_high);

	mask = 0x7 << reg_shift;

	reg_val &= ~mask;
	reg_val |= (remap_level << reg_shift) & mask;

	reg_val_lvl &= ~mask;
	reg_val_lvl |= (remap_level << reg_shift) & mask;

	DPU_REG_WRITE(c, VBIF_XINL_QOS_RP_REMAP_000 + reg_high, reg_val);
	DPU_REG_WRITE(c, VBIF_XINL_QOS_LVL_REMAP_000 + reg_high, reg_val_lvl);
}