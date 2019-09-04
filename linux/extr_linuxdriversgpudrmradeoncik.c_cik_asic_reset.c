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
typedef  scalar_t__ u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ cik_gpu_check_soft_reset (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_gpu_pci_config_reset (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_gpu_soft_reset (struct radeon_device*,scalar_t__) ; 
 int /*<<< orphan*/  r600_set_bios_scratch_engine_hung (struct radeon_device*,int) ; 
 scalar_t__ radeon_hard_reset ; 

int cik_asic_reset(struct radeon_device *rdev, bool hard)
{
	u32 reset_mask;

	if (hard) {
		cik_gpu_pci_config_reset(rdev);
		return 0;
	}

	reset_mask = cik_gpu_check_soft_reset(rdev);

	if (reset_mask)
		r600_set_bios_scratch_engine_hung(rdev, true);

	/* try soft reset */
	cik_gpu_soft_reset(rdev, reset_mask);

	reset_mask = cik_gpu_check_soft_reset(rdev);

	/* try pci config reset */
	if (reset_mask && radeon_hard_reset)
		cik_gpu_pci_config_reset(rdev);

	reset_mask = cik_gpu_check_soft_reset(rdev);

	if (!reset_mask)
		r600_set_bios_scratch_engine_hung(rdev, false);

	return 0;
}