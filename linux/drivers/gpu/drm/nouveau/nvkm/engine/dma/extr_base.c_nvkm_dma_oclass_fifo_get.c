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
struct nvkm_oclass {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvkm_dma_sclass ; 

__attribute__((used)) static int
nvkm_dma_oclass_fifo_get(struct nvkm_oclass *oclass, int index)
{
	const int count = ARRAY_SIZE(nvkm_dma_sclass);
	if (index < count) {
		oclass->base = nvkm_dma_sclass[index];
		return index;
	}
	return count;
}