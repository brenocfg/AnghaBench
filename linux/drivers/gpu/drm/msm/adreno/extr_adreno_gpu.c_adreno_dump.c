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
typedef  int uint32_t ;
struct msm_gpu {int /*<<< orphan*/  name; } ;
struct adreno_gpu {int* registers; } ;

/* Variables and functions */
 int gpu_read (struct msm_gpu*,int) ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

void adreno_dump(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	int i;

	if (!adreno_gpu->registers)
		return;

	/* dump these out in a form that can be parsed by demsm: */
	printk("IO:region %s 00000000 00020000\n", gpu->name);
	for (i = 0; adreno_gpu->registers[i] != ~0; i += 2) {
		uint32_t start = adreno_gpu->registers[i];
		uint32_t end   = adreno_gpu->registers[i+1];
		uint32_t addr;

		for (addr = start; addr <= end; addr++) {
			uint32_t val = gpu_read(gpu, addr);
			printk("IO:R %08x %08x\n", addr<<2, val);
		}
	}
}