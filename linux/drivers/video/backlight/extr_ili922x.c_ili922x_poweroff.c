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
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_POWER_CONTROL_1 ; 
 int /*<<< orphan*/  REG_POWER_CONTROL_2 ; 
 int /*<<< orphan*/  REG_POWER_CONTROL_3 ; 
 int /*<<< orphan*/  REG_POWER_CONTROL_4 ; 
 int ili922x_write (struct spi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ili922x_poweroff(struct spi_device *spi)
{
	int ret;

	/* Power off */
	ret = ili922x_write(spi, REG_POWER_CONTROL_1, 0x0000);
	usleep_range(10000, 10500);
	ret += ili922x_write(spi, REG_POWER_CONTROL_2, 0x0000);
	ret += ili922x_write(spi, REG_POWER_CONTROL_3, 0x0000);
	msleep(40);
	ret += ili922x_write(spi, REG_POWER_CONTROL_4, 0x0000);
	msleep(40);

	return ret;
}