#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nvkm_instmem {int /*<<< orphan*/  ramht; } ;
struct nvkm_fifo_chan {int dummy; } ;
struct nv04_fifo_chan {TYPE_3__* fifo; } ;
struct TYPE_10__ {int /*<<< orphan*/  mutex; TYPE_1__* device; } ;
struct TYPE_9__ {TYPE_5__ subdev; } ;
struct TYPE_7__ {TYPE_4__ engine; } ;
struct TYPE_8__ {TYPE_2__ base; } ;
struct TYPE_6__ {struct nvkm_instmem* imem; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nv04_fifo_chan* nv04_fifo_chan (struct nvkm_fifo_chan*) ; 
 int /*<<< orphan*/  nvkm_ramht_remove (int /*<<< orphan*/ ,int) ; 

void
nv04_fifo_dma_object_dtor(struct nvkm_fifo_chan *base, int cookie)
{
	struct nv04_fifo_chan *chan = nv04_fifo_chan(base);
	struct nvkm_instmem *imem = chan->fifo->base.engine.subdev.device->imem;

	mutex_lock(&chan->fifo->base.engine.subdev.mutex);
	nvkm_ramht_remove(imem->ramht, cookie);
	mutex_unlock(&chan->fifo->base.engine.subdev.mutex);
}