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
struct nvkm_fifo_func {scalar_t__ uevent_init; } ;
struct nvkm_fifo {int nr; int /*<<< orphan*/  kevent; int /*<<< orphan*/  cevent; int /*<<< orphan*/  uevent; int /*<<< orphan*/  engine; int /*<<< orphan*/  mask; int /*<<< orphan*/  lock; int /*<<< orphan*/  chan; struct nvkm_fifo_func const* func; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NVKM_FIFO_CHID_NR ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nvkm_engine_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int,int /*<<< orphan*/ *) ; 
 int nvkm_event_init (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_fifo ; 
 int /*<<< orphan*/  nvkm_fifo_cevent_func ; 
 int /*<<< orphan*/  nvkm_fifo_kevent_func ; 
 int /*<<< orphan*/  nvkm_fifo_uevent_func ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int
nvkm_fifo_ctor(const struct nvkm_fifo_func *func, struct nvkm_device *device,
	       int index, int nr, struct nvkm_fifo *fifo)
{
	int ret;

	fifo->func = func;
	INIT_LIST_HEAD(&fifo->chan);
	spin_lock_init(&fifo->lock);

	if (WARN_ON(fifo->nr > NVKM_FIFO_CHID_NR))
		fifo->nr = NVKM_FIFO_CHID_NR;
	else
		fifo->nr = nr;
	bitmap_clear(fifo->mask, 0, fifo->nr);

	ret = nvkm_engine_ctor(&nvkm_fifo, device, index, true, &fifo->engine);
	if (ret)
		return ret;

	if (func->uevent_init) {
		ret = nvkm_event_init(&nvkm_fifo_uevent_func, 1, 1,
				      &fifo->uevent);
		if (ret)
			return ret;
	}

	ret = nvkm_event_init(&nvkm_fifo_cevent_func, 1, 1, &fifo->cevent);
	if (ret)
		return ret;

	return nvkm_event_init(&nvkm_fifo_kevent_func, 1, nr, &fifo->kevent);
}