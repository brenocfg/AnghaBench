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
struct lock_class_key {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int gpiochip_add_irqchip(struct gpio_chip *gpiochip,
				       struct lock_class_key *lock_key,
				       struct lock_class_key *request_key)
{
	return 0;
}