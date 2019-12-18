#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_vmid_mgr {int /*<<< orphan*/  lock; struct amdgpu_vmid* ids; } ;
struct amdgpu_vmid {scalar_t__ oa_size; scalar_t__ oa_base; scalar_t__ gws_size; scalar_t__ gws_base; scalar_t__ gds_size; scalar_t__ gds_base; scalar_t__ owner; } ;
struct TYPE_2__ {struct amdgpu_vmid_mgr* id_mgr; } ;
struct amdgpu_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void amdgpu_vmid_reset(struct amdgpu_device *adev, unsigned vmhub,
		       unsigned vmid)
{
	struct amdgpu_vmid_mgr *id_mgr = &adev->vm_manager.id_mgr[vmhub];
	struct amdgpu_vmid *id = &id_mgr->ids[vmid];

	mutex_lock(&id_mgr->lock);
	id->owner = 0;
	id->gds_base = 0;
	id->gds_size = 0;
	id->gws_base = 0;
	id->gws_size = 0;
	id->oa_base = 0;
	id->oa_size = 0;
	mutex_unlock(&id_mgr->lock);
}