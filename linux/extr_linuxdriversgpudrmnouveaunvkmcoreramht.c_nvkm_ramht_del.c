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
struct nvkm_ramht {int /*<<< orphan*/  gpuobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_gpuobj_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (struct nvkm_ramht*) ; 

void
nvkm_ramht_del(struct nvkm_ramht **pramht)
{
	struct nvkm_ramht *ramht = *pramht;
	if (ramht) {
		nvkm_gpuobj_del(&ramht->gpuobj);
		vfree(*pramht);
		*pramht = NULL;
	}
}