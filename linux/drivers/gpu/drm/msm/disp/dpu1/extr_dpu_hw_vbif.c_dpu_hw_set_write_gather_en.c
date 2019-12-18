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
typedef  scalar_t__ u32 ;
struct dpu_hw_blk_reg_map {int dummy; } ;
struct dpu_hw_vbif {struct dpu_hw_blk_reg_map hw; } ;

/* Variables and functions */
 scalar_t__ BIT (scalar_t__) ; 
 scalar_t__ DPU_REG_READ (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_REG_WRITE (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ MAX_XIN_COUNT ; 
 int /*<<< orphan*/  VBIF_WRITE_GATHER_EN ; 

__attribute__((used)) static void dpu_hw_set_write_gather_en(struct dpu_hw_vbif *vbif, u32 xin_id)
{
	struct dpu_hw_blk_reg_map *c;
	u32 reg_val;

	if (!vbif || xin_id >= MAX_XIN_COUNT)
		return;

	c = &vbif->hw;

	reg_val = DPU_REG_READ(c, VBIF_WRITE_GATHER_EN);
	reg_val |= BIT(xin_id);
	DPU_REG_WRITE(c, VBIF_WRITE_GATHER_EN, reg_val);
}