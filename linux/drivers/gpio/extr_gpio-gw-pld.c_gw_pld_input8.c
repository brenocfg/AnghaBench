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
struct gw_pld {int /*<<< orphan*/  out; int /*<<< orphan*/  client; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 struct gw_pld* gpiochip_get_data (struct gpio_chip*) ; 
 int i2c_smbus_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gw_pld_input8(struct gpio_chip *gc, unsigned offset)
{
	struct gw_pld *gw = gpiochip_get_data(gc);

	gw->out |= BIT(offset);
	return i2c_smbus_write_byte(gw->client, gw->out);
}