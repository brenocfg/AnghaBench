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
struct amdgpu_vm_pt_cursor {int dummy; } ;
struct amdgpu_vm {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ amdgpu_vm_pt_descendant (struct amdgpu_device*,struct amdgpu_vm_pt_cursor*) ; 
 int /*<<< orphan*/  amdgpu_vm_pt_start (struct amdgpu_device*,struct amdgpu_vm*,int /*<<< orphan*/ ,struct amdgpu_vm_pt_cursor*) ; 

__attribute__((used)) static void amdgpu_vm_pt_first_dfs(struct amdgpu_device *adev,
				   struct amdgpu_vm *vm,
				   struct amdgpu_vm_pt_cursor *start,
				   struct amdgpu_vm_pt_cursor *cursor)
{
	if (start)
		*cursor = *start;
	else
		amdgpu_vm_pt_start(adev, vm, 0, cursor);
	while (amdgpu_vm_pt_descendant(adev, cursor));
}