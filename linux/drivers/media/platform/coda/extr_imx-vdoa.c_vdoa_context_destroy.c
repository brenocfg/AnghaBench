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
struct vdoa_data {int /*<<< orphan*/  vdoa_clk; struct vdoa_ctx* curr_ctx; } ;
struct vdoa_ctx {struct vdoa_data* vdoa; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vdoa_ctx*) ; 
 int /*<<< orphan*/  vdoa_wait_for_completion (struct vdoa_ctx*) ; 

void vdoa_context_destroy(struct vdoa_ctx *ctx)
{
	struct vdoa_data *vdoa = ctx->vdoa;

	if (vdoa->curr_ctx == ctx) {
		vdoa_wait_for_completion(vdoa->curr_ctx);
		vdoa->curr_ctx = NULL;
	}

	clk_disable_unprepare(vdoa->vdoa_clk);
	kfree(ctx);
}