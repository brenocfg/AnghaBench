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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_rcar_config_general_input_output_mode (struct gpio_chip*,unsigned int,int) ; 
 int /*<<< orphan*/  gpio_rcar_set (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int gpio_rcar_direction_output(struct gpio_chip *chip, unsigned offset,
				      int value)
{
	/* write GPIO value to output before selecting output mode of pin */
	gpio_rcar_set(chip, offset, value);
	gpio_rcar_config_general_input_output_mode(chip, offset, true);
	return 0;
}