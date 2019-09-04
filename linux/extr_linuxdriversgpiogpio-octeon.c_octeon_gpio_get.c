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
typedef  unsigned long long u64 ;
struct octeon_gpio {scalar_t__ register_base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ RX_DAT ; 
 unsigned long long cvmx_read_csr (scalar_t__) ; 
 struct octeon_gpio* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int octeon_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct octeon_gpio *gpio = gpiochip_get_data(chip);
	u64 read_bits = cvmx_read_csr(gpio->register_base + RX_DAT);

	return ((1ull << offset) & read_bits) != 0;
}