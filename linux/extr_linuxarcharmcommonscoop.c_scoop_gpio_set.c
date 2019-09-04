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
struct scoop_dev {int /*<<< orphan*/  scoop_lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __scoop_gpio_set (struct scoop_dev*,unsigned int,int) ; 
 struct scoop_dev* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void scoop_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	struct scoop_dev *sdev = gpiochip_get_data(chip);
	unsigned long flags;

	spin_lock_irqsave(&sdev->scoop_lock, flags);

	__scoop_gpio_set(sdev, offset, value);

	spin_unlock_irqrestore(&sdev->scoop_lock, flags);
}