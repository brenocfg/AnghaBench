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
struct nvkm_oclass {TYPE_1__* engn; int /*<<< orphan*/  base; } ;
struct nvkm_fifo {int dummy; } ;
struct gk104_fifo {TYPE_2__* func; } ;
struct TYPE_3__ {int /*<<< orphan*/  user; scalar_t__ ctor; } ;
struct TYPE_4__ {TYPE_1__ chan; TYPE_1__ user; } ;

/* Variables and functions */
 struct gk104_fifo* gk104_fifo (struct nvkm_fifo*) ; 

__attribute__((used)) static int
gk104_fifo_class_get(struct nvkm_fifo *base, int index,
		     struct nvkm_oclass *oclass)
{
	struct gk104_fifo *fifo = gk104_fifo(base);
	int c = 0;

	if (fifo->func->user.ctor && c++ == index) {
		oclass->base =  fifo->func->user.user;
		oclass->engn = &fifo->func->user;
		return 0;
	}

	if (fifo->func->chan.ctor && c++ == index) {
		oclass->base =  fifo->func->chan.user;
		oclass->engn = &fifo->func->chan;
		return 0;
	}

	return c;
}