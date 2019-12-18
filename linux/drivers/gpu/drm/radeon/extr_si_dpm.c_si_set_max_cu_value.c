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
struct si_power_info {int max_cu; } ;
struct radeon_device {scalar_t__ family; TYPE_1__* pdev; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 scalar_t__ CHIP_VERDE ; 
 struct si_power_info* si_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void si_set_max_cu_value(struct radeon_device *rdev)
{
	struct si_power_info *si_pi = si_get_pi(rdev);

	if (rdev->family == CHIP_VERDE) {
		switch (rdev->pdev->device) {
		case 0x6820:
		case 0x6825:
		case 0x6821:
		case 0x6823:
		case 0x6827:
			si_pi->max_cu = 10;
			break;
		case 0x682D:
		case 0x6824:
		case 0x682F:
		case 0x6826:
			si_pi->max_cu = 8;
			break;
		case 0x6828:
		case 0x6830:
		case 0x6831:
		case 0x6838:
		case 0x6839:
		case 0x683D:
			si_pi->max_cu = 10;
			break;
		case 0x683B:
		case 0x683F:
		case 0x6829:
			si_pi->max_cu = 8;
			break;
		default:
			si_pi->max_cu = 0;
			break;
		}
	} else {
		si_pi->max_cu = 0;
	}
}