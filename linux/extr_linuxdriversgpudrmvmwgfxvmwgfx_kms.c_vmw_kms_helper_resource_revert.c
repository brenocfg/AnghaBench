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
struct vmw_validation_ctx {int /*<<< orphan*/  buf; struct vmw_resource* res; } ;
struct vmw_resource {TYPE_1__* dev_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmdbuf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_bo_unreference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_kms_helper_buffer_revert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_resource_unreserve (struct vmw_resource*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void vmw_kms_helper_resource_revert(struct vmw_validation_ctx *ctx)
{
	struct vmw_resource *res = ctx->res;

	vmw_kms_helper_buffer_revert(ctx->buf);
	vmw_bo_unreference(&ctx->buf);
	vmw_resource_unreserve(res, false, NULL, 0);
	mutex_unlock(&res->dev_priv->cmdbuf_mutex);
}