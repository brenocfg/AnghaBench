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
struct dpu_hw_ctl {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpu_hw_blk_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dpu_hw_ctl*) ; 

void dpu_hw_ctl_destroy(struct dpu_hw_ctl *ctx)
{
	if (ctx)
		dpu_hw_blk_destroy(&ctx->base);
	kfree(ctx);
}