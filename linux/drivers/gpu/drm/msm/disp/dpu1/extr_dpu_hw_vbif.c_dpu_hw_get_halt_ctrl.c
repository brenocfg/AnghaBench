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
 int BIT (int) ; 
 int DPU_REG_READ (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VBIF_XIN_HALT_CTRL1 ; 

__attribute__((used)) static bool dpu_hw_get_halt_ctrl(struct dpu_hw_vbif *vbif,
		u32 xin_id)
{
	struct dpu_hw_blk_reg_map *c = &vbif->hw;
	u32 reg_val;

	reg_val = DPU_REG_READ(c, VBIF_XIN_HALT_CTRL1);

	return (reg_val & BIT(xin_id)) ? true : false;
}