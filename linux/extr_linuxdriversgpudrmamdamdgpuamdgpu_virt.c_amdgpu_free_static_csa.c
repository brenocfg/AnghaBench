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
struct TYPE_2__ {int /*<<< orphan*/  csa_vmid0_addr; int /*<<< orphan*/  csa_obj; } ;
struct amdgpu_device {TYPE_1__ virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void amdgpu_free_static_csa(struct amdgpu_device *adev) {
	amdgpu_bo_free_kernel(&adev->virt.csa_obj,
						&adev->virt.csa_vmid0_addr,
						NULL);
}