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
typedef  size_t u32 ;
struct nvkm_ramht {size_t size; TYPE_1__* data; } ;
struct nvkm_gpuobj {int dummy; } ;
struct TYPE_2__ {int chid; size_t handle; struct nvkm_gpuobj* inst; } ;

/* Variables and functions */
 size_t nvkm_ramht_hash (struct nvkm_ramht*,int,size_t) ; 

struct nvkm_gpuobj *
nvkm_ramht_search(struct nvkm_ramht *ramht, int chid, u32 handle)
{
	u32 co, ho;

	co = ho = nvkm_ramht_hash(ramht, chid, handle);
	do {
		if (ramht->data[co].chid == chid) {
			if (ramht->data[co].handle == handle)
				return ramht->data[co].inst;
		}

		if (++co >= ramht->size)
			co = 0;
	} while (co != ho);

	return NULL;
}