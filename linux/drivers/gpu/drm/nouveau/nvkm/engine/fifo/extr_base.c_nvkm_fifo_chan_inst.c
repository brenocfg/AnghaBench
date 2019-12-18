#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct nvkm_fifo_chan {int dummy; } ;
struct nvkm_fifo {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct nvkm_fifo_chan* nvkm_fifo_chan_inst_locked (struct nvkm_fifo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct nvkm_fifo_chan *
nvkm_fifo_chan_inst(struct nvkm_fifo *fifo, u64 inst, unsigned long *rflags)
{
	struct nvkm_fifo_chan *chan;
	unsigned long flags;
	spin_lock_irqsave(&fifo->lock, flags);
	if ((chan = nvkm_fifo_chan_inst_locked(fifo, inst))) {
		*rflags = flags;
		return chan;
	}
	spin_unlock_irqrestore(&fifo->lock, flags);
	return NULL;
}