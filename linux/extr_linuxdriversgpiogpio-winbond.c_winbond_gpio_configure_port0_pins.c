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
 unsigned int WB_SIO_REG_G1MF_FS_GPIO1 ; 
 unsigned int WB_SIO_REG_G1MF_FS_MASK ; 
 int /*<<< orphan*/  WB_SIO_REG_GPIO1_MF ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int) ; 
 unsigned int winbond_sio_reg_read (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  winbond_sio_reg_write (unsigned long,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void winbond_gpio_configure_port0_pins(unsigned long base)
{
	unsigned int val;

	val = winbond_sio_reg_read(base, WB_SIO_REG_GPIO1_MF);
	if ((val & WB_SIO_REG_G1MF_FS_MASK) == WB_SIO_REG_G1MF_FS_GPIO1)
		return;

	pr_warn("GPIO1 pins were connected to something else (%.2x), fixing\n",
		val);

	val &= ~WB_SIO_REG_G1MF_FS_MASK;
	val |= WB_SIO_REG_G1MF_FS_GPIO1;

	winbond_sio_reg_write(base, WB_SIO_REG_GPIO1_MF, val);
}