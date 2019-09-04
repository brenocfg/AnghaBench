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
 int ENODEV ; 
 unsigned int WB_SIO_CHIP_ID_W83627UHG ; 
 unsigned int WB_SIO_CHIP_ID_W83627UHG_MASK ; 
 int /*<<< orphan*/  WB_SIO_REG_CHIP_LSB ; 
 int /*<<< orphan*/  WB_SIO_REG_CHIP_MSB ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_notice (char*,unsigned long,unsigned int) ; 
 int winbond_sio_enter (unsigned long) ; 
 int /*<<< orphan*/  winbond_sio_leave (unsigned long) ; 
 unsigned int winbond_sio_reg_read (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int winbond_gpio_check_chip(unsigned long base)
{
	int ret;
	unsigned int chip;

	ret = winbond_sio_enter(base);
	if (ret)
		return ret;

	chip = winbond_sio_reg_read(base, WB_SIO_REG_CHIP_MSB) << 8;
	chip |= winbond_sio_reg_read(base, WB_SIO_REG_CHIP_LSB);

	pr_notice("chip ID at %lx is %.4x\n", base, chip);

	if ((chip & WB_SIO_CHIP_ID_W83627UHG_MASK) !=
	    WB_SIO_CHIP_ID_W83627UHG) {
		pr_err("not an our chip\n");
		ret = -ENODEV;
	}

	winbond_sio_leave(base);

	return ret;
}