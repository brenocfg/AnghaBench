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
struct gw_pld {int /*<<< orphan*/  client; } ;
struct gpio_chip {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 struct gw_pld* gpiochip_get_data (struct gpio_chip*) ; 
 int i2c_smbus_read_byte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gw_pld_get8(struct gpio_chip *gc, unsigned offset)
{
	struct gw_pld *gw = gpiochip_get_data(gc);
	s32 val;

	val = i2c_smbus_read_byte(gw->client);

	return (val < 0) ? 0 : !!(val & BIT(offset));
}