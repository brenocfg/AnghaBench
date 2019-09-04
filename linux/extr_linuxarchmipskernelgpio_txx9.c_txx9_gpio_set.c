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
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  txx9_gpio_lock ; 
 int /*<<< orphan*/  txx9_gpio_set_raw (unsigned int,int) ; 

__attribute__((used)) static void txx9_gpio_set(struct gpio_chip *chip, unsigned int offset,
			  int value)
{
	unsigned long flags;
	spin_lock_irqsave(&txx9_gpio_lock, flags);
	txx9_gpio_set_raw(offset, value);
	mmiowb();
	spin_unlock_irqrestore(&txx9_gpio_lock, flags);
}