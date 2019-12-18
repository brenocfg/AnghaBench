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
struct sch_gpio {int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLV ; 
 struct sch_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  sch_gpio_reg_set (struct sch_gpio*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sch_gpio_set(struct gpio_chip *gc, unsigned gpio_num, int val)
{
	struct sch_gpio *sch = gpiochip_get_data(gc);

	spin_lock(&sch->lock);
	sch_gpio_reg_set(sch, gpio_num, GLV, val);
	spin_unlock(&sch->lock);
}