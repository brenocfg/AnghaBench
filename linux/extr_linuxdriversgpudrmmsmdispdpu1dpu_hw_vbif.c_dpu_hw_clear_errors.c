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
 int DPU_REG_READ (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_REG_WRITE (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VBIF_XIN_CLR_ERR ; 
 int /*<<< orphan*/  VBIF_XIN_PND_ERR ; 
 int /*<<< orphan*/  VBIF_XIN_SRC_ERR ; 

__attribute__((used)) static void dpu_hw_clear_errors(struct dpu_hw_vbif *vbif,
		u32 *pnd_errors, u32 *src_errors)
{
	struct dpu_hw_blk_reg_map *c;
	u32 pnd, src;

	if (!vbif)
		return;
	c = &vbif->hw;
	pnd = DPU_REG_READ(c, VBIF_XIN_PND_ERR);
	src = DPU_REG_READ(c, VBIF_XIN_SRC_ERR);

	if (pnd_errors)
		*pnd_errors = pnd;
	if (src_errors)
		*src_errors = src;

	DPU_REG_WRITE(c, VBIF_XIN_CLR_ERR, pnd | src);
}