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
struct sbsm_data {int /*<<< orphan*/  client; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  SBSM_CMD_BATSYSSTATE ; 
 struct sbsm_data* gpiochip_get_data (struct gpio_chip*) ; 
 int sbsm_read_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sbsm_gpio_get_value(struct gpio_chip *gc, unsigned int off)
{
	struct sbsm_data *data = gpiochip_get_data(gc);
	int ret;

	ret = sbsm_read_word(data->client, SBSM_CMD_BATSYSSTATE);
	if (ret < 0)
		return ret;

	return ret & BIT(off);
}