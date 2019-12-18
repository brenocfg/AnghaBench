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
struct ras_manager {int /*<<< orphan*/ * ent; } ;
struct ras_common_if {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 struct ras_manager* amdgpu_ras_find_obj (struct amdgpu_device*,struct ras_common_if*) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_obj (struct ras_manager*) ; 

void amdgpu_ras_debugfs_remove(struct amdgpu_device *adev,
		struct ras_common_if *head)
{
	struct ras_manager *obj = amdgpu_ras_find_obj(adev, head);

	if (!obj || !obj->ent)
		return;

	debugfs_remove(obj->ent);
	obj->ent = NULL;
	put_obj(obj);
}