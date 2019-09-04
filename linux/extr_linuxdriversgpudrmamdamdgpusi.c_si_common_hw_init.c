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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  si_fix_pci_max_read_req_size (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_init_golden_registers (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_pcie_gen3_enable (struct amdgpu_device*) ; 
 int /*<<< orphan*/  si_program_aspm (struct amdgpu_device*) ; 

__attribute__((used)) static int si_common_hw_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	si_fix_pci_max_read_req_size(adev);
	si_init_golden_registers(adev);
	si_pcie_gen3_enable(adev);
	si_program_aspm(adev);

	return 0;
}