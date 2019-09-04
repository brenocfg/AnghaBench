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
typedef  int /*<<< orphan*/  u32 ;
struct dpu_hw_ctl {int /*<<< orphan*/  pending_flush_mask; } ;

/* Variables and functions */

__attribute__((used)) static inline void dpu_hw_ctl_update_pending_flush(struct dpu_hw_ctl *ctx,
		u32 flushbits)
{
	ctx->pending_flush_mask |= flushbits;
}