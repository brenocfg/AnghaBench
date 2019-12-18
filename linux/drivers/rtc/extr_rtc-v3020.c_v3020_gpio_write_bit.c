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
struct v3020 {TYPE_1__* gpio; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 size_t V3020_CS ; 
 size_t V3020_IO ; 
 size_t V3020_WR ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void v3020_gpio_write_bit(struct v3020 *chip, unsigned char bit)
{
	gpio_direction_output(chip->gpio[V3020_IO].gpio, bit);
	gpio_set_value(chip->gpio[V3020_CS].gpio, 0);
	gpio_set_value(chip->gpio[V3020_WR].gpio, 0);
	udelay(1);
	gpio_set_value(chip->gpio[V3020_WR].gpio, 1);
	gpio_set_value(chip->gpio[V3020_CS].gpio, 1);
}