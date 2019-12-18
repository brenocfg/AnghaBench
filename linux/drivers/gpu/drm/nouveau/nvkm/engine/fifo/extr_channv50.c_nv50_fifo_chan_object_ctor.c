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
struct nvkm_object {int handle; TYPE_2__* engine; } ;
struct nvkm_fifo_chan {int dummy; } ;
struct nv50_fifo_chan {int /*<<< orphan*/  ramht; } ;
struct TYPE_3__ {int index; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NVKM_ENGINE_DMAOBJ 131 
#define  NVKM_ENGINE_GR 130 
#define  NVKM_ENGINE_MPEG 129 
#define  NVKM_ENGINE_SW 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct nv50_fifo_chan* nv50_fifo_chan (struct nvkm_fifo_chan*) ; 
 int nvkm_ramht_insert (int /*<<< orphan*/ ,struct nvkm_object*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
nv50_fifo_chan_object_ctor(struct nvkm_fifo_chan *base,
			   struct nvkm_object *object)
{
	struct nv50_fifo_chan *chan = nv50_fifo_chan(base);
	u32 handle = object->handle;
	u32 context;

	switch (object->engine->subdev.index) {
	case NVKM_ENGINE_DMAOBJ:
	case NVKM_ENGINE_SW    : context = 0x00000000; break;
	case NVKM_ENGINE_GR    : context = 0x00100000; break;
	case NVKM_ENGINE_MPEG  : context = 0x00200000; break;
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	return nvkm_ramht_insert(chan->ramht, object, 0, 4, handle, context);
}