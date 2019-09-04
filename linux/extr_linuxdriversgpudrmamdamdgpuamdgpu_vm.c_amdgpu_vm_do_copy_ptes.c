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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_pte_update_params {int src; int /*<<< orphan*/  ib; int /*<<< orphan*/  adev; } ;
struct amdgpu_bo {int dummy; } ;

/* Variables and functions */
 scalar_t__ amdgpu_bo_gpu_offset (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_vm_copy_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int) ; 
 int /*<<< orphan*/  trace_amdgpu_vm_copy_ptes (int,int,unsigned int) ; 

__attribute__((used)) static void amdgpu_vm_do_copy_ptes(struct amdgpu_pte_update_params *params,
				   struct amdgpu_bo *bo,
				   uint64_t pe, uint64_t addr,
				   unsigned count, uint32_t incr,
				   uint64_t flags)
{
	uint64_t src = (params->src + (addr >> 12) * 8);

	pe += amdgpu_bo_gpu_offset(bo);
	trace_amdgpu_vm_copy_ptes(pe, src, count);

	amdgpu_vm_copy_pte(params->adev, params->ib, pe, src, count);
}