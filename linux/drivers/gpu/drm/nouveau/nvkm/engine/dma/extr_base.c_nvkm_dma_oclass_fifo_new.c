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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_oclass {TYPE_2__* engine; } ;
struct nvkm_object {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 int nvkm_dma_oclass_new (int /*<<< orphan*/ ,struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,struct nvkm_object**) ; 

__attribute__((used)) static int
nvkm_dma_oclass_fifo_new(const struct nvkm_oclass *oclass, void *data, u32 size,
			 struct nvkm_object **pobject)
{
	return nvkm_dma_oclass_new(oclass->engine->subdev.device,
				   oclass, data, size, pobject);
}