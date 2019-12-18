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
struct TYPE_2__ {int tx_oe; } ;
union cvmx_gpio_bit_cfgx {scalar_t__ u64; TYPE_1__ s; } ;
struct octeon_gpio {scalar_t__ register_base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ bit_cfg_reg (unsigned int) ; 
 int /*<<< orphan*/  cvmx_write_csr (scalar_t__,scalar_t__) ; 
 struct octeon_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  octeon_gpio_set (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int octeon_gpio_dir_out(struct gpio_chip *chip, unsigned offset,
			       int value)
{
	struct octeon_gpio *gpio = gpiochip_get_data(chip);
	union cvmx_gpio_bit_cfgx cfgx;

	octeon_gpio_set(chip, offset, value);

	cfgx.u64 = 0;
	cfgx.s.tx_oe = 1;

	cvmx_write_csr(gpio->register_base + bit_cfg_reg(offset), cfgx.u64);
	return 0;
}