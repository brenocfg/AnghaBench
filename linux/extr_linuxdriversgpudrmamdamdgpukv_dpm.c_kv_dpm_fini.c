#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_ps; TYPE_3__* priv; TYPE_3__* ps; } ;
struct TYPE_5__ {TYPE_1__ dpm; } ;
struct amdgpu_device {TYPE_2__ pm; } ;
struct TYPE_6__ {struct TYPE_6__* ps_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_free_extended_power_table (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 

__attribute__((used)) static void kv_dpm_fini(struct amdgpu_device *adev)
{
	int i;

	for (i = 0; i < adev->pm.dpm.num_ps; i++) {
		kfree(adev->pm.dpm.ps[i].ps_priv);
	}
	kfree(adev->pm.dpm.ps);
	kfree(adev->pm.dpm.priv);
	amdgpu_free_extended_power_table(adev);
}