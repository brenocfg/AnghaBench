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
typedef  int u64 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOWER_GPIO_ENABLE ; 
 int /*<<< orphan*/  UPPER_GPIO_ENABLE ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int upper_32_bits (int) ; 

void r600_voltage_control_enable_pins(struct radeon_device *rdev,
				      u64 mask)
{
	WREG32(LOWER_GPIO_ENABLE, mask & 0xffffffff);
	WREG32(UPPER_GPIO_ENABLE, upper_32_bits(mask));
}