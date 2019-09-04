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
struct vmw_cmdbuf_context {scalar_t__ num_hw_submitted; int /*<<< orphan*/  preempted; int /*<<< orphan*/  submitted; int /*<<< orphan*/  hw_submitted; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmw_cmdbuf_ctx_init(struct vmw_cmdbuf_context *ctx)
{
	INIT_LIST_HEAD(&ctx->hw_submitted);
	INIT_LIST_HEAD(&ctx->submitted);
	INIT_LIST_HEAD(&ctx->preempted);
	ctx->num_hw_submitted = 0;
}