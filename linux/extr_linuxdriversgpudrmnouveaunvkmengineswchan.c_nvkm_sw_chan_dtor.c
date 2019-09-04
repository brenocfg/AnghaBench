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
struct nvkm_sw_chan {int /*<<< orphan*/  head; int /*<<< orphan*/  event; TYPE_2__* func; struct nvkm_sw* sw; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct nvkm_sw {TYPE_1__ engine; } ;
struct nvkm_object {int dummy; } ;
struct TYPE_4__ {void* (* dtor ) (struct nvkm_sw_chan*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_event_fini (int /*<<< orphan*/ *) ; 
 struct nvkm_sw_chan* nvkm_sw_chan (struct nvkm_object*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 void* stub1 (struct nvkm_sw_chan*) ; 

__attribute__((used)) static void *
nvkm_sw_chan_dtor(struct nvkm_object *object)
{
	struct nvkm_sw_chan *chan = nvkm_sw_chan(object);
	struct nvkm_sw *sw = chan->sw;
	unsigned long flags;
	void *data = chan;

	if (chan->func->dtor)
		data = chan->func->dtor(chan);
	nvkm_event_fini(&chan->event);

	spin_lock_irqsave(&sw->engine.lock, flags);
	list_del(&chan->head);
	spin_unlock_irqrestore(&sw->engine.lock, flags);
	return data;
}