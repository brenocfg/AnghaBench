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
struct dpu_hw_ctl {int /*<<< orphan*/  hw; int /*<<< orphan*/  pending_flush_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_START ; 
 int /*<<< orphan*/  DPU_REG_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dpu_hw_ctl_get_flush_register (struct dpu_hw_ctl*) ; 
 int /*<<< orphan*/  trace_dpu_hw_ctl_trigger_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dpu_hw_ctl_trigger_start(struct dpu_hw_ctl *ctx)
{
	trace_dpu_hw_ctl_trigger_start(ctx->pending_flush_mask,
				       dpu_hw_ctl_get_flush_register(ctx));
	DPU_REG_WRITE(&ctx->hw, CTL_START, 0x1);
}