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
struct amdgpu_device {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_ASIC_RESET_DATA ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void amdgpu_device_pci_config_reset(struct amdgpu_device *adev)
{
	pci_write_config_dword(adev->pdev, 0x7c, AMDGPU_ASIC_RESET_DATA);
}