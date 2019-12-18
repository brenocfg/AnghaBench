#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tee_ioctl_cancel_arg {int /*<<< orphan*/  session; int /*<<< orphan*/  cancel_id; } ;
struct tee_context {TYPE_3__* teedev; } ;
struct TYPE_6__ {TYPE_2__* desc; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int (* cancel_req ) (struct tee_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct tee_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tee_client_cancel_req(struct tee_context *ctx,
			  struct tee_ioctl_cancel_arg *arg)
{
	if (!ctx->teedev->desc->ops->cancel_req)
		return -EINVAL;
	return ctx->teedev->desc->ops->cancel_req(ctx, arg->cancel_id,
						  arg->session);
}