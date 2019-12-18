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
struct amdgpu_bo_list {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_list_free ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void amdgpu_bo_list_put(struct amdgpu_bo_list *list)
{
	kref_put(&list->refcount, amdgpu_bo_list_free);
}