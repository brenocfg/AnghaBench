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
struct dpu_hw_mdp {struct dpu_hw_blk_reg_map hw; } ;
struct dpu_danger_safe_status {int mdp; int* sspp; } ;

/* Variables and functions */
 int DPU_REG_READ (struct dpu_hw_blk_reg_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAFE_STATUS ; 
 size_t SSPP_CURSOR0 ; 
 size_t SSPP_CURSOR1 ; 
 size_t SSPP_DMA0 ; 
 size_t SSPP_DMA1 ; 
 size_t SSPP_DMA2 ; 
 size_t SSPP_DMA3 ; 
 size_t SSPP_RGB0 ; 
 size_t SSPP_RGB1 ; 
 size_t SSPP_RGB2 ; 
 size_t SSPP_RGB3 ; 
 size_t SSPP_VIG0 ; 
 size_t SSPP_VIG1 ; 
 size_t SSPP_VIG2 ; 
 size_t SSPP_VIG3 ; 

__attribute__((used)) static void dpu_hw_get_safe_status(struct dpu_hw_mdp *mdp,
		struct dpu_danger_safe_status *status)
{
	struct dpu_hw_blk_reg_map *c;
	u32 value;

	if (!mdp || !status)
		return;

	c = &mdp->hw;

	value = DPU_REG_READ(c, SAFE_STATUS);
	status->mdp = (value >> 0) & 0x1;
	status->sspp[SSPP_VIG0] = (value >> 4) & 0x1;
	status->sspp[SSPP_VIG1] = (value >> 6) & 0x1;
	status->sspp[SSPP_VIG2] = (value >> 8) & 0x1;
	status->sspp[SSPP_VIG3] = (value >> 10) & 0x1;
	status->sspp[SSPP_RGB0] = (value >> 12) & 0x1;
	status->sspp[SSPP_RGB1] = (value >> 14) & 0x1;
	status->sspp[SSPP_RGB2] = (value >> 16) & 0x1;
	status->sspp[SSPP_RGB3] = (value >> 18) & 0x1;
	status->sspp[SSPP_DMA0] = (value >> 20) & 0x1;
	status->sspp[SSPP_DMA1] = (value >> 22) & 0x1;
	status->sspp[SSPP_DMA2] = (value >> 28) & 0x1;
	status->sspp[SSPP_DMA3] = (value >> 30) & 0x1;
	status->sspp[SSPP_CURSOR0] = (value >> 24) & 0x1;
	status->sspp[SSPP_CURSOR1] = (value >> 26) & 0x1;
}