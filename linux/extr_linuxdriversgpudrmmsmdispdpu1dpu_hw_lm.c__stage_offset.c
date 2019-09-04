#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dpu_lm_sub_blks {int maxblendstages; int* blendstage_base; } ;
struct dpu_hw_mixer {TYPE_1__* cap; } ;
typedef  enum dpu_stage { ____Placeholder_dpu_stage } dpu_stage ;
struct TYPE_2__ {struct dpu_lm_sub_blks* sblk; } ;

/* Variables and functions */
 int DPU_STAGE_0 ; 
 int DPU_STAGE_BASE ; 
 int EINVAL ; 

__attribute__((used)) static inline int _stage_offset(struct dpu_hw_mixer *ctx, enum dpu_stage stage)
{
	const struct dpu_lm_sub_blks *sblk = ctx->cap->sblk;
	int rc;

	if (stage == DPU_STAGE_BASE)
		rc = -EINVAL;
	else if (stage <= sblk->maxblendstages)
		rc = sblk->blendstage_base[stage - DPU_STAGE_0];
	else
		rc = -EINVAL;

	return rc;
}