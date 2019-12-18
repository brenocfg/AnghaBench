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
 int EINVAL ; 
 unsigned int NR_VX855_GPI ; 
 int /*<<< orphan*/  vx855gpio_set (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int vx855gpio_direction_output(struct gpio_chip *gpio,
				      unsigned int nr, int val)
{
	/* True GPI cannot be switched to output mode */
	if (nr < NR_VX855_GPI)
		return -EINVAL;

	/* True GPO don't need to be switched to output mode,
	 * and GPIO are open-drain, i.e. also need no switching,
	 * so all we do is set the level */
	vx855gpio_set(gpio, nr, val);

	return 0;
}