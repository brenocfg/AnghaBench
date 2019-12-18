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
struct sysinfo {scalar_t__ mem_unit; scalar_t__ totalhigh; scalar_t__ totalram; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  amdgpu_amdkfd_gpuvm_init_mem_limits () ; 
 scalar_t__ amdgpu_amdkfd_total_mem_size ; 
 int kgd2kfd_init () ; 
 int /*<<< orphan*/  si_meminfo (struct sysinfo*) ; 

int amdgpu_amdkfd_init(void)
{
	struct sysinfo si;
	int ret;

	si_meminfo(&si);
	amdgpu_amdkfd_total_mem_size = si.totalram - si.totalhigh;
	amdgpu_amdkfd_total_mem_size *= si.mem_unit;

#ifdef CONFIG_HSA_AMD
	ret = kgd2kfd_init();
	amdgpu_amdkfd_gpuvm_init_mem_limits();
#else
	ret = -ENOENT;
#endif

	return ret;
}