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
struct mpc512x_lpbfifo_request {int dummy; } ;
struct TYPE_2__ {int wait_lpbfifo_irq; int wait_lpbfifo_callback; struct mpc512x_lpbfifo_request* req; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 TYPE_1__ lpbfifo ; 
 int mpc512x_lpbfifo_kick () ; 

__attribute__((used)) static int mpc512x_lpbfifo_submit_locked(struct mpc512x_lpbfifo_request *req)
{
	int ret = 0;

	if (!lpbfifo.regs)
		return -ENODEV;

	/* Check whether a transfer is in progress */
	if (lpbfifo.req)
		return -EBUSY;

	lpbfifo.wait_lpbfifo_irq = true;
	lpbfifo.wait_lpbfifo_callback = true;
	lpbfifo.req = req;

	ret = mpc512x_lpbfifo_kick();
	if (ret != 0)
		lpbfifo.req = NULL; /* Set the FIFO as idle */

	return ret;
}