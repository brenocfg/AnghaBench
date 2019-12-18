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
struct TYPE_3__ {int /*<<< orphan*/  done; } ;
struct request_context {struct request_context* buf; TYPE_2__* outurb; int /*<<< orphan*/  timer; TYPE_1__ done; int /*<<< orphan*/  refcount; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct request_context*) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_2__*) ; 

__attribute__((used)) static void ezusb_request_context_put(struct request_context *ctx)
{
	if (!refcount_dec_and_test(&ctx->refcount))
		return;

	WARN_ON(!ctx->done.done);
	BUG_ON(ctx->outurb->status == -EINPROGRESS);
	BUG_ON(timer_pending(&ctx->timer));
	usb_free_urb(ctx->outurb);
	kfree(ctx->buf);
	kfree(ctx);
}