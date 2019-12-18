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
 int EINVAL ; 
 int /*<<< orphan*/  SIO_REG_MFUNCT1 ; 
 int /*<<< orphan*/  SIO_REG_MFUNCT3 ; 
 int /*<<< orphan*/  SIO_REG_ROM_ADDR_SEL ; 
 int f71862fg_pin ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  superio_clear_bit (unsigned short,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  superio_set_bit (unsigned short,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int f71862fg_pin_configure(unsigned short ioaddr)
{
	/* When ioaddr is non-zero the calling function has to take care of
	   mutex handling and superio preparation! */

	if (f71862fg_pin == 63) {
		if (ioaddr) {
			/* SPI must be disabled first to use this pin! */
			superio_clear_bit(ioaddr, SIO_REG_ROM_ADDR_SEL, 6);
			superio_set_bit(ioaddr, SIO_REG_MFUNCT3, 4);
		}
	} else if (f71862fg_pin == 56) {
		if (ioaddr)
			superio_set_bit(ioaddr, SIO_REG_MFUNCT1, 1);
	} else {
		pr_err("Invalid argument f71862fg_pin=%d\n", f71862fg_pin);
		return -EINVAL;
	}
	return 0;
}