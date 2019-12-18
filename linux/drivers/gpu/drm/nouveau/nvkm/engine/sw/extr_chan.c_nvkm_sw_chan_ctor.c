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
struct nvkm_sw_chan_func {int dummy; } ;
struct nvkm_sw_chan {int /*<<< orphan*/  event; int /*<<< orphan*/  head; struct nvkm_fifo_chan* fifo; struct nvkm_sw* sw; struct nvkm_sw_chan_func const* func; int /*<<< orphan*/  object; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct nvkm_sw {TYPE_1__ engine; int /*<<< orphan*/  chan; } ;
struct nvkm_oclass {int dummy; } ;
struct nvkm_fifo_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nvkm_event_init (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_object_ctor (int /*<<< orphan*/ *,struct nvkm_oclass const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_sw_chan ; 
 int /*<<< orphan*/  nvkm_sw_chan_event ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
nvkm_sw_chan_ctor(const struct nvkm_sw_chan_func *func, struct nvkm_sw *sw,
		  struct nvkm_fifo_chan *fifo, const struct nvkm_oclass *oclass,
		  struct nvkm_sw_chan *chan)
{
	unsigned long flags;

	nvkm_object_ctor(&nvkm_sw_chan, oclass, &chan->object);
	chan->func = func;
	chan->sw = sw;
	chan->fifo = fifo;
	spin_lock_irqsave(&sw->engine.lock, flags);
	list_add(&chan->head, &sw->chan);
	spin_unlock_irqrestore(&sw->engine.lock, flags);

	return nvkm_event_init(&nvkm_sw_chan_event, 1, 1, &chan->event);
}