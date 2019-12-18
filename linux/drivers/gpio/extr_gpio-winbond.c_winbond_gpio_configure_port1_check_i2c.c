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
struct TYPE_2__ {int i2cgpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  WB_SIO_REG_I2CPS_I2CFS ; 
 int /*<<< orphan*/  WB_SIO_REG_I2C_PS ; 
 TYPE_1__ params ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  winbond_sio_reg_btest (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void winbond_gpio_configure_port1_check_i2c(unsigned long base)
{
	params.i2cgpio = !winbond_sio_reg_btest(base, WB_SIO_REG_I2C_PS,
						WB_SIO_REG_I2CPS_I2CFS);
	if (!params.i2cgpio)
		pr_warn("disabling GPIO2.5 and GPIO2.6 as I2C is enabled\n");
}