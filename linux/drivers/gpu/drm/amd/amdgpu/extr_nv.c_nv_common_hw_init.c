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
struct amdgpu_device {TYPE_1__* nbio_funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init_registers ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nv_enable_doorbell_aperture (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  nv_pcie_gen3_enable (struct amdgpu_device*) ; 
 int /*<<< orphan*/  nv_program_aspm (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 

__attribute__((used)) static int nv_common_hw_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	/* enable pcie gen2/3 link */
	nv_pcie_gen3_enable(adev);
	/* enable aspm */
	nv_program_aspm(adev);
	/* setup nbio registers */
	adev->nbio_funcs->init_registers(adev);
	/* enable the doorbell aperture */
	nv_enable_doorbell_aperture(adev, true);

	return 0;
}