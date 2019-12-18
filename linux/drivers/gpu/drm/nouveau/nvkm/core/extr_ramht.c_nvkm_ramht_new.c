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
typedef  int u32 ;
struct nvkm_ramht {int size; int /*<<< orphan*/  gpuobj; struct nvkm_gpuobj* parent; struct nvkm_device* device; TYPE_1__* data; int /*<<< orphan*/  bits; } ;
struct nvkm_gpuobj {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_2__ {int chid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  data ; 
 int nvkm_gpuobj_new (struct nvkm_device*,int,int,int,struct nvkm_gpuobj*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_ramht_del (struct nvkm_ramht**) ; 
 int /*<<< orphan*/  order_base_2 (int) ; 
 int /*<<< orphan*/  struct_size (struct nvkm_ramht*,int /*<<< orphan*/ ,int) ; 
 struct nvkm_ramht* vzalloc (int /*<<< orphan*/ ) ; 

int
nvkm_ramht_new(struct nvkm_device *device, u32 size, u32 align,
	       struct nvkm_gpuobj *parent, struct nvkm_ramht **pramht)
{
	struct nvkm_ramht *ramht;
	int ret, i;

	if (!(ramht = *pramht = vzalloc(struct_size(ramht, data, (size >> 3)))))
		return -ENOMEM;

	ramht->device = device;
	ramht->parent = parent;
	ramht->size = size >> 3;
	ramht->bits = order_base_2(ramht->size);
	for (i = 0; i < ramht->size; i++)
		ramht->data[i].chid = -1;

	ret = nvkm_gpuobj_new(ramht->device, size, align, true,
			      ramht->parent, &ramht->gpuobj);
	if (ret)
		nvkm_ramht_del(pramht);
	return ret;
}