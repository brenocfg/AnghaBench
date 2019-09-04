#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int /*<<< orphan*/  base; } ;
struct TYPE_7__ {int /*<<< orphan*/  base; } ;
struct TYPE_6__ {int /*<<< orphan*/  base; } ;
struct dpu_sspp_sub_blks {TYPE_4__ csc_blk; TYPE_3__ scaler_blk; TYPE_2__ src_blk; } ;
struct dpu_hw_pipe {TYPE_1__* cap; } ;
struct TYPE_5__ {struct dpu_sspp_sub_blks* sblk; } ;

/* Variables and functions */
#define  DPU_SSPP_CSC 133 
#define  DPU_SSPP_CSC_10BIT 132 
#define  DPU_SSPP_SCALER_QSEED2 131 
#define  DPU_SSPP_SCALER_QSEED3 130 
#define  DPU_SSPP_SCALER_RGB 129 
#define  DPU_SSPP_SRC 128 
 int EINVAL ; 

__attribute__((used)) static inline int _sspp_subblk_offset(struct dpu_hw_pipe *ctx,
		int s_id,
		u32 *idx)
{
	int rc = 0;
	const struct dpu_sspp_sub_blks *sblk = ctx->cap->sblk;

	if (!ctx)
		return -EINVAL;

	switch (s_id) {
	case DPU_SSPP_SRC:
		*idx = sblk->src_blk.base;
		break;
	case DPU_SSPP_SCALER_QSEED2:
	case DPU_SSPP_SCALER_QSEED3:
	case DPU_SSPP_SCALER_RGB:
		*idx = sblk->scaler_blk.base;
		break;
	case DPU_SSPP_CSC:
	case DPU_SSPP_CSC_10BIT:
		*idx = sblk->csc_blk.base;
		break;
	default:
		rc = -EINVAL;
	}

	return rc;
}