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
struct nvkm_object {int dummy; } ;
struct nvkm_fifo_chan {TYPE_2__* inst; TYPE_2__* push; scalar_t__ vmm; scalar_t__ user; int /*<<< orphan*/  head; int /*<<< orphan*/  chid; TYPE_1__* func; struct nvkm_fifo* fifo; } ;
struct nvkm_fifo {int /*<<< orphan*/  lock; int /*<<< orphan*/  mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  memory; } ;
struct TYPE_3__ {void* (* dtor ) (struct nvkm_fifo_chan*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct nvkm_fifo_chan* nvkm_fifo_chan (struct nvkm_object*) ; 
 int /*<<< orphan*/  nvkm_gpuobj_del (TYPE_2__**) ; 
 int /*<<< orphan*/  nvkm_vmm_part (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_vmm_unref (scalar_t__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 void* stub1 (struct nvkm_fifo_chan*) ; 

__attribute__((used)) static void *
nvkm_fifo_chan_dtor(struct nvkm_object *object)
{
	struct nvkm_fifo_chan *chan = nvkm_fifo_chan(object);
	struct nvkm_fifo *fifo = chan->fifo;
	void *data = chan->func->dtor(chan);
	unsigned long flags;

	spin_lock_irqsave(&fifo->lock, flags);
	if (!list_empty(&chan->head)) {
		__clear_bit(chan->chid, fifo->mask);
		list_del(&chan->head);
	}
	spin_unlock_irqrestore(&fifo->lock, flags);

	if (chan->user)
		iounmap(chan->user);

	if (chan->vmm) {
		nvkm_vmm_part(chan->vmm, chan->inst->memory);
		nvkm_vmm_unref(&chan->vmm);
	}

	nvkm_gpuobj_del(&chan->push);
	nvkm_gpuobj_del(&chan->inst);
	return data;
}