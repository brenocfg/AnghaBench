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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_oclass {int /*<<< orphan*/  engine; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_fifo {TYPE_1__* func; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_2__ {int (* class_new ) (struct nvkm_fifo*,struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,struct nvkm_object**) ;} ;

/* Variables and functions */
 struct nvkm_fifo* nvkm_fifo (int /*<<< orphan*/ ) ; 
 int stub1 (struct nvkm_fifo*,struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,struct nvkm_object**) ; 

__attribute__((used)) static int
nvkm_fifo_class_new_(struct nvkm_device *device,
		     const struct nvkm_oclass *oclass, void *data, u32 size,
		     struct nvkm_object **pobject)
{
	struct nvkm_fifo *fifo = nvkm_fifo(oclass->engine);
	return fifo->func->class_new(fifo, oclass, data, size, pobject);
}