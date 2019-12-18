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
struct meson_pinctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_DIR ; 
 int meson_pinconf_get_gpio_bit (struct meson_pinctrl*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_pinconf_get_output(struct meson_pinctrl *pc,
				    unsigned int pin)
{
	int ret = meson_pinconf_get_gpio_bit(pc, pin, REG_DIR);

	if (ret < 0)
		return ret;

	return !ret;
}