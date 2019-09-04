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
struct radeon_device {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_ASIC_RESET_DATA ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void radeon_pci_config_reset(struct radeon_device *rdev)
{
	pci_write_config_dword(rdev->pdev, 0x7c, RADEON_ASIC_RESET_DATA);
}