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
struct nvkm_fifo {int /*<<< orphan*/  lock; TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* recover_chan ) (struct nvkm_fifo*,int) ;} ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_fifo*,int) ; 

void
nvkm_fifo_recover_chan(struct nvkm_fifo *fifo, int chid)
{
	unsigned long flags;
	if (WARN_ON(!fifo->func->recover_chan))
		return;
	spin_lock_irqsave(&fifo->lock, flags);
	fifo->func->recover_chan(fifo, chid);
	spin_unlock_irqrestore(&fifo->lock, flags);
}