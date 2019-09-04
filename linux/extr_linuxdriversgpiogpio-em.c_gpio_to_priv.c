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
struct em_gio_priv {int dummy; } ;

/* Variables and functions */
 struct em_gio_priv* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static inline struct em_gio_priv *gpio_to_priv(struct gpio_chip *chip)
{
	return gpiochip_get_data(chip);
}