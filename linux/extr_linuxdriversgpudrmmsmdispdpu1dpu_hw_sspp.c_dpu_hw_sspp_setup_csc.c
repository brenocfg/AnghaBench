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
typedef  int /*<<< orphan*/  u32 ;
struct dpu_hw_pipe {int /*<<< orphan*/  hw; TYPE_1__* cap; } ;
struct dpu_csc_cfg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 scalar_t__ CSC_10BIT_OFFSET ; 
 int /*<<< orphan*/  DPU_SSPP_CSC ; 
 int /*<<< orphan*/  DPU_SSPP_CSC_10BIT ; 
 scalar_t__ _sspp_subblk_offset (struct dpu_hw_pipe*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpu_hw_csc_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dpu_csc_cfg*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dpu_hw_sspp_setup_csc(struct dpu_hw_pipe *ctx,
		struct dpu_csc_cfg *data)
{
	u32 idx;
	bool csc10 = false;

	if (_sspp_subblk_offset(ctx, DPU_SSPP_CSC, &idx) || !data)
		return;

	if (test_bit(DPU_SSPP_CSC_10BIT, &ctx->cap->features)) {
		idx += CSC_10BIT_OFFSET;
		csc10 = true;
	}

	dpu_hw_csc_setup(&ctx->hw, idx, data, csc10);
}