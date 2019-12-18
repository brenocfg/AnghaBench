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
struct nvkm_memory {int dummy; } ;
struct nvkm_gpuobj {int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_gpuobj* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_memory_addr (struct nvkm_memory*) ; 
 int /*<<< orphan*/  nvkm_memory_size (struct nvkm_memory*) ; 

int
nvkm_gpuobj_wrap(struct nvkm_memory *memory, struct nvkm_gpuobj **pgpuobj)
{
	if (!(*pgpuobj = kzalloc(sizeof(**pgpuobj), GFP_KERNEL)))
		return -ENOMEM;

	(*pgpuobj)->addr = nvkm_memory_addr(memory);
	(*pgpuobj)->size = nvkm_memory_size(memory);
	return 0;
}