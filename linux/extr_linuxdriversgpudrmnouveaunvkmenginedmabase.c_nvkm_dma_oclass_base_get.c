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
struct nvkm_sclass {int dummy; } ;
struct nvkm_oclass {struct nvkm_sclass const* engn; struct nvkm_sclass base; } ;
struct nvkm_device_oclass {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct nvkm_sclass*) ; 
 struct nvkm_device_oclass nvkm_dma_oclass_base ; 
 struct nvkm_sclass* nvkm_dma_sclass ; 

__attribute__((used)) static int
nvkm_dma_oclass_base_get(struct nvkm_oclass *sclass, int index,
			 const struct nvkm_device_oclass **class)
{
	const int count = ARRAY_SIZE(nvkm_dma_sclass);
	if (index < count) {
		const struct nvkm_sclass *oclass = &nvkm_dma_sclass[index];
		sclass->base = oclass[0];
		sclass->engn = oclass;
		*class = &nvkm_dma_oclass_base;
		return index;
	}
	return count;
}