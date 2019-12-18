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
struct vmw_validation_context {int /*<<< orphan*/  bo_list; int /*<<< orphan*/  resource_ctx_list; int /*<<< orphan*/  resource_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct vmw_validation_context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
vmw_validation_context_init(struct vmw_validation_context *ctx)
{
	memset(ctx, 0, sizeof(*ctx));
	INIT_LIST_HEAD(&ctx->resource_list);
	INIT_LIST_HEAD(&ctx->resource_ctx_list);
	INIT_LIST_HEAD(&ctx->bo_list);
}