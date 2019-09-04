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
typedef  int /*<<< orphan*/  uint64_t ;
struct amdgpu_vm {int /*<<< orphan*/  va; } ;
struct amdgpu_bo_va_mapping {int dummy; } ;

/* Variables and functions */
 struct amdgpu_bo_va_mapping* amdgpu_vm_it_iter_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct amdgpu_bo_va_mapping *amdgpu_vm_bo_lookup_mapping(struct amdgpu_vm *vm,
							 uint64_t addr)
{
	return amdgpu_vm_it_iter_first(&vm->va, addr, addr);
}