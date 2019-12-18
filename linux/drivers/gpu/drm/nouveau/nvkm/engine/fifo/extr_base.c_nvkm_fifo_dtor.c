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
struct nvkm_fifo {int /*<<< orphan*/  uevent; int /*<<< orphan*/  cevent; int /*<<< orphan*/  kevent; TYPE_1__* func; } ;
struct nvkm_engine {int dummy; } ;
struct TYPE_2__ {void* (* dtor ) (struct nvkm_fifo*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_event_fini (int /*<<< orphan*/ *) ; 
 struct nvkm_fifo* nvkm_fifo (struct nvkm_engine*) ; 
 void* stub1 (struct nvkm_fifo*) ; 

__attribute__((used)) static void *
nvkm_fifo_dtor(struct nvkm_engine *engine)
{
	struct nvkm_fifo *fifo = nvkm_fifo(engine);
	void *data = fifo;
	if (fifo->func->dtor)
		data = fifo->func->dtor(fifo);
	nvkm_event_fini(&fifo->kevent);
	nvkm_event_fini(&fifo->cevent);
	nvkm_event_fini(&fifo->uevent);
	return data;
}