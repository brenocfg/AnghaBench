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
typedef  int u32 ;
struct mpc512x_lpbfifo_request {scalar_t__ dir; int /*<<< orphan*/  (* callback ) (struct mpc512x_lpbfifo_request*) ;} ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int wait_lpbfifo_irq; int /*<<< orphan*/  lock; struct mpc512x_lpbfifo_request* req; scalar_t__ wait_lpbfifo_callback; TYPE_1__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ MPC512X_LPBFIFO_REQ_DIR_READ ; 
 int MPC512X_SCLPC_FIFO_RESET ; 
 int MPC512X_SCLPC_RESET ; 
 int MPC512X_SCLPC_SUCCESS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 TYPE_2__ lpbfifo ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct mpc512x_lpbfifo_request*) ; 

__attribute__((used)) static irqreturn_t mpc512x_lpbfifo_irq(int irq, void *param)
{
	struct device *dev = (struct device *)param;
	struct mpc512x_lpbfifo_request *req = NULL;
	unsigned long flags;
	u32 status;

	spin_lock_irqsave(&lpbfifo.lock, flags);

	if (!lpbfifo.regs)
		goto end;

	req = lpbfifo.req;
	if (!req || req->dir == MPC512X_LPBFIFO_REQ_DIR_READ) {
		dev_err(dev, "bogus LPBFIFO IRQ\n");
		goto end;
	}

	status = in_be32(&lpbfifo.regs->status);
	if (status != MPC512X_SCLPC_SUCCESS) {
		dev_err(dev, "DMA transfer from RAM to peripheral failed\n");
		out_be32(&lpbfifo.regs->enable,
				MPC512X_SCLPC_RESET | MPC512X_SCLPC_FIFO_RESET);
		goto end;
	}
	/* Clear the interrupt flag */
	out_be32(&lpbfifo.regs->status, MPC512X_SCLPC_SUCCESS);

	lpbfifo.wait_lpbfifo_irq = false;

	if (lpbfifo.wait_lpbfifo_callback)
		goto end;

	/* Transfer is finished, set the FIFO as idle */
	lpbfifo.req = NULL;

	spin_unlock_irqrestore(&lpbfifo.lock, flags);

	if (req->callback)
		req->callback(req);

	return IRQ_HANDLED;

 end:
	spin_unlock_irqrestore(&lpbfifo.lock, flags);
	return IRQ_HANDLED;
}