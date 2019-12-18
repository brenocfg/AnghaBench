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
struct nvkm_object {int dummy; } ;
struct nvkm_gpuobj {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int nvkm_object_bind (int /*<<< orphan*/ ,struct nvkm_gpuobj*,int,struct nvkm_gpuobj**) ; 
 TYPE_1__* nvkm_oproxy (struct nvkm_object*) ; 

__attribute__((used)) static int
nvkm_oproxy_bind(struct nvkm_object *object, struct nvkm_gpuobj *parent,
		 int align, struct nvkm_gpuobj **pgpuobj)
{
	return nvkm_object_bind(nvkm_oproxy(object)->object,
				parent, align, pgpuobj);
}