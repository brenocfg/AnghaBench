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
struct s5k5baf_gpio {int /*<<< orphan*/  level; int /*<<< orphan*/  gpio; } ;
struct s5k5baf {struct s5k5baf_gpio* gpios; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void s5k5baf_gpio_deassert(struct s5k5baf *state, int id)
{
	struct s5k5baf_gpio *gpio = &state->gpios[id];

	gpio_set_value(gpio->gpio, !gpio->level);
}