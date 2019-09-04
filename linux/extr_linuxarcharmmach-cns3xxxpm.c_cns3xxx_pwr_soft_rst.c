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
 int /*<<< orphan*/  cns3xxx_pwr_soft_rst_force (unsigned int) ; 

void cns3xxx_pwr_soft_rst(unsigned int block)
{
	static unsigned int soft_reset;

	if (soft_reset & block) {
		/* SPI/I2C/GPIO use the same block, reset once. */
		return;
	} else {
		soft_reset |= block;
	}
	cns3xxx_pwr_soft_rst_force(block);
}