#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uld_ctx {TYPE_1__* dev; } ;
struct TYPE_4__ {scalar_t__ oc_mw_kva; scalar_t__ bar2_kva; } ;
struct TYPE_3__ {int /*<<< orphan*/  ibdev; TYPE_2__ rdev; int /*<<< orphan*/  atids; int /*<<< orphan*/  stids; int /*<<< orphan*/  hwtids; int /*<<< orphan*/  wait; int /*<<< orphan*/  mrs; int /*<<< orphan*/  qps; int /*<<< orphan*/  cqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  c4iw_rdev_close (TYPE_2__*) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_empty (int /*<<< orphan*/ *) ; 

void c4iw_dealloc(struct uld_ctx *ctx)
{
	c4iw_rdev_close(&ctx->dev->rdev);
	WARN_ON(!xa_empty(&ctx->dev->cqs));
	WARN_ON(!xa_empty(&ctx->dev->qps));
	WARN_ON(!xa_empty(&ctx->dev->mrs));
	wait_event(ctx->dev->wait, xa_empty(&ctx->dev->hwtids));
	WARN_ON(!xa_empty(&ctx->dev->stids));
	WARN_ON(!xa_empty(&ctx->dev->atids));
	if (ctx->dev->rdev.bar2_kva)
		iounmap(ctx->dev->rdev.bar2_kva);
	if (ctx->dev->rdev.oc_mw_kva)
		iounmap(ctx->dev->rdev.oc_mw_kva);
	ib_dealloc_device(&ctx->dev->ibdev);
	ctx->dev = NULL;
}