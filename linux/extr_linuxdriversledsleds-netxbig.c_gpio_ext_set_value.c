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
struct netxbig_gpio_ext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_ext_enable_select (struct netxbig_gpio_ext*) ; 
 int /*<<< orphan*/  gpio_ext_lock ; 
 int /*<<< orphan*/  gpio_ext_set_addr (struct netxbig_gpio_ext*,int) ; 
 int /*<<< orphan*/  gpio_ext_set_data (struct netxbig_gpio_ext*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gpio_ext_set_value(struct netxbig_gpio_ext *gpio_ext,
			       int addr, int value)
{
	unsigned long flags;

	spin_lock_irqsave(&gpio_ext_lock, flags);
	gpio_ext_set_addr(gpio_ext, addr);
	gpio_ext_set_data(gpio_ext, value);
	gpio_ext_enable_select(gpio_ext);
	spin_unlock_irqrestore(&gpio_ext_lock, flags);
}