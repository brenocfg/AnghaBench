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
struct urb {int /*<<< orphan*/  status; scalar_t__ context; } ;
struct TYPE_2__ {int busy; int /*<<< orphan*/  finished; int /*<<< orphan*/  status; } ;
struct imon_context {TYPE_1__ tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static void usb_tx_callback(struct urb *urb)
{
	struct imon_context *ictx;

	if (!urb)
		return;
	ictx = (struct imon_context *)urb->context;
	if (!ictx)
		return;

	ictx->tx.status = urb->status;

	/* notify waiters that write has finished */
	ictx->tx.busy = false;
	smp_rmb(); /* ensure later readers know we're not busy */
	complete(&ictx->tx.finished);
}