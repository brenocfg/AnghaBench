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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int family; TYPE_1__* pdev; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  CHIP_ARUBA 129 
#define  CHIP_CAYMAN 128 
 int /*<<< orphan*/  cayman_golden_registers ; 
 int /*<<< orphan*/  cayman_golden_registers2 ; 
 int /*<<< orphan*/  dvst_golden_registers ; 
 int /*<<< orphan*/  dvst_golden_registers2 ; 
 int /*<<< orphan*/  radeon_program_register_sequence (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  scrapper_golden_registers ; 

__attribute__((used)) static void ni_init_golden_registers(struct radeon_device *rdev)
{
	switch (rdev->family) {
	case CHIP_CAYMAN:
		radeon_program_register_sequence(rdev,
						 cayman_golden_registers,
						 (const u32)ARRAY_SIZE(cayman_golden_registers));
		radeon_program_register_sequence(rdev,
						 cayman_golden_registers2,
						 (const u32)ARRAY_SIZE(cayman_golden_registers2));
		break;
	case CHIP_ARUBA:
		if ((rdev->pdev->device == 0x9900) ||
		    (rdev->pdev->device == 0x9901) ||
		    (rdev->pdev->device == 0x9903) ||
		    (rdev->pdev->device == 0x9904) ||
		    (rdev->pdev->device == 0x9905) ||
		    (rdev->pdev->device == 0x9906) ||
		    (rdev->pdev->device == 0x9907) ||
		    (rdev->pdev->device == 0x9908) ||
		    (rdev->pdev->device == 0x9909) ||
		    (rdev->pdev->device == 0x990A) ||
		    (rdev->pdev->device == 0x990B) ||
		    (rdev->pdev->device == 0x990C) ||
		    (rdev->pdev->device == 0x990D) ||
		    (rdev->pdev->device == 0x990E) ||
		    (rdev->pdev->device == 0x990F) ||
		    (rdev->pdev->device == 0x9910) ||
		    (rdev->pdev->device == 0x9913) ||
		    (rdev->pdev->device == 0x9917) ||
		    (rdev->pdev->device == 0x9918)) {
			radeon_program_register_sequence(rdev,
							 dvst_golden_registers,
							 (const u32)ARRAY_SIZE(dvst_golden_registers));
			radeon_program_register_sequence(rdev,
							 dvst_golden_registers2,
							 (const u32)ARRAY_SIZE(dvst_golden_registers2));
		} else {
			radeon_program_register_sequence(rdev,
							 scrapper_golden_registers,
							 (const u32)ARRAY_SIZE(scrapper_golden_registers));
			radeon_program_register_sequence(rdev,
							 dvst_golden_registers2,
							 (const u32)ARRAY_SIZE(dvst_golden_registers2));
		}
		break;
	default:
		break;
	}
}