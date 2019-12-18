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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOPAD_A ; 
 int /*<<< orphan*/  GPIOPAD_EN ; 
 int /*<<< orphan*/  GPIOPAD_MASK ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void r600_voltage_control_deactivate_static_control(struct radeon_device *rdev,
						    u64 mask)
{
	u32 gpio;

	gpio = RREG32(GPIOPAD_MASK);
	gpio &= ~mask;
	WREG32(GPIOPAD_MASK, gpio);

	gpio = RREG32(GPIOPAD_EN);
	gpio &= ~mask;
	WREG32(GPIOPAD_EN, gpio);

	gpio = RREG32(GPIOPAD_A);
	gpio &= ~mask;
	WREG32(GPIOPAD_A, gpio);
}