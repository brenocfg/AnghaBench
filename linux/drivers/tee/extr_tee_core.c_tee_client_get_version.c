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
struct tee_ioctl_version_data {int dummy; } ;
struct tee_context {TYPE_3__* teedev; } ;
struct TYPE_6__ {TYPE_2__* desc; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_version ) (TYPE_3__*,struct tee_ioctl_version_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct tee_ioctl_version_data*) ; 

void tee_client_get_version(struct tee_context *ctx,
			    struct tee_ioctl_version_data *vers)
{
	ctx->teedev->desc->ops->get_version(ctx->teedev, vers);
}