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
typedef  unsigned int u8 ;
struct htcpld_chip {unsigned int cache_out; unsigned int cache_in; } ;
struct gpio_chip {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int EINVAL ; 
 struct htcpld_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int htcpld_chip_get(struct gpio_chip *chip, unsigned offset)
{
	struct htcpld_chip *chip_data = gpiochip_get_data(chip);
	u8 cache;

	if (!strncmp(chip->label, "htcpld-out", 10)) {
		cache = chip_data->cache_out;
	} else if (!strncmp(chip->label, "htcpld-in", 9)) {
		cache = chip_data->cache_in;
	} else
		return -EINVAL;

	return (cache >> offset) & 1;
}