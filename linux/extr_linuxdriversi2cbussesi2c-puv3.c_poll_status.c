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
 int /*<<< orphan*/  I2C_RXFLR ; 
 int /*<<< orphan*/  I2C_STATUS ; 
 unsigned long I2C_STATUS_TFNF ; 
 int /*<<< orphan*/  I2C_TAR ; 
 int I2C_TAR_EEPROM ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static short poll_status(unsigned long bit)
{
	int loop_cntr = 1000;

	if (bit & I2C_STATUS_TFNF) {
		do {
			udelay(10);
		} while (!(readl(I2C_STATUS) & bit) && (--loop_cntr > 0));
	} else {
		/* RXRDY handler */
		do {
			if (readl(I2C_TAR) == I2C_TAR_EEPROM)
				msleep(20);
			else
				udelay(10);
		} while (!(readl(I2C_RXFLR) & 0xf) && (--loop_cntr > 0));
	}

	return (loop_cntr > 0);
}