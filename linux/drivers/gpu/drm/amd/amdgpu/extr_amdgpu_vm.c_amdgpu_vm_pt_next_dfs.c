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
struct amdgpu_vm_pt_cursor {int /*<<< orphan*/ * entry; int /*<<< orphan*/  parent; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_vm_pt_ancestor (struct amdgpu_vm_pt_cursor*) ; 
 scalar_t__ amdgpu_vm_pt_descendant (struct amdgpu_device*,struct amdgpu_vm_pt_cursor*) ; 
 scalar_t__ amdgpu_vm_pt_sibling (struct amdgpu_device*,struct amdgpu_vm_pt_cursor*) ; 

__attribute__((used)) static void amdgpu_vm_pt_next_dfs(struct amdgpu_device *adev,
				  struct amdgpu_vm_pt_cursor *cursor)
{
	if (!cursor->entry)
		return;

	if (!cursor->parent)
		cursor->entry = NULL;
	else if (amdgpu_vm_pt_sibling(adev, cursor))
		while (amdgpu_vm_pt_descendant(adev, cursor));
	else
		amdgpu_vm_pt_ancestor(cursor);
}