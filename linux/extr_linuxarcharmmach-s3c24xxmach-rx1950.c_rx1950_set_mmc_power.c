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

/* Variables and functions */
#define  MMC_POWER_OFF 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 
 int /*<<< orphan*/  S3C2410_GPJ (int) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rx1950_set_mmc_power(unsigned char power_mode, unsigned short vdd)
{
	switch (power_mode) {
	case MMC_POWER_OFF:
		gpio_direction_output(S3C2410_GPJ(1), 0);
		break;
	case MMC_POWER_UP:
	case MMC_POWER_ON:
		gpio_direction_output(S3C2410_GPJ(1), 1);
		break;
	default:
		break;
	}
}