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
struct dma_fence {int dummy; } ;
struct amdgpu_vm_update_params {int /*<<< orphan*/  adev; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_asic_flush_hdp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static int amdgpu_vm_cpu_commit(struct amdgpu_vm_update_params *p,
				struct dma_fence **fence)
{
	/* Flush HDP */
	mb();
	amdgpu_asic_flush_hdp(p->adev, NULL);
	return 0;
}