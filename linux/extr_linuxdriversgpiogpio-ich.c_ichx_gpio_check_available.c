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
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int use_gpio; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 TYPE_1__ ichx_priv ; 

__attribute__((used)) static bool ichx_gpio_check_available(struct gpio_chip *gpio, unsigned nr)
{
	return !!(ichx_priv.use_gpio & BIT(nr / 32));
}