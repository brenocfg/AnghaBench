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
struct TYPE_3__ {int /*<<< orphan*/  ibdev; TYPE_2__ rdev; int /*<<< orphan*/  atid_idr; int /*<<< orphan*/  stid_idr; int /*<<< orphan*/  hwtid_idr; int /*<<< orphan*/  wait; int /*<<< orphan*/  mmidr; int /*<<< orphan*/  qpidr; int /*<<< orphan*/  cqidr; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  c4iw_rdev_close (TYPE_2__*) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void c4iw_dealloc(struct uld_ctx *ctx)
{
	c4iw_rdev_close(&ctx->dev->rdev);
	WARN_ON_ONCE(!idr_is_empty(&ctx->dev->cqidr));
	idr_destroy(&ctx->dev->cqidr);
	WARN_ON_ONCE(!idr_is_empty(&ctx->dev->qpidr));
	idr_destroy(&ctx->dev->qpidr);
	WARN_ON_ONCE(!idr_is_empty(&ctx->dev->mmidr));
	idr_destroy(&ctx->dev->mmidr);
	wait_event(ctx->dev->wait, idr_is_empty(&ctx->dev->hwtid_idr));
	idr_destroy(&ctx->dev->hwtid_idr);
	idr_destroy(&ctx->dev->stid_idr);
	idr_destroy(&ctx->dev->atid_idr);
	if (ctx->dev->rdev.bar2_kva)
		iounmap(ctx->dev->rdev.bar2_kva);
	if (ctx->dev->rdev.oc_mw_kva)
		iounmap(ctx->dev->rdev.oc_mw_kva);
	ib_dealloc_device(&ctx->dev->ibdev);
	ctx->dev = NULL;
}