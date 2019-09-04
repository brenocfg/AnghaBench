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
struct cs5535_gpio_chip {int /*<<< orphan*/  lock; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_INPUT_AUX1 ; 
 int /*<<< orphan*/  GPIO_OUTPUT_AUX1 ; 
 int /*<<< orphan*/  GPIO_OUTPUT_AUX2 ; 
 int /*<<< orphan*/  __cs5535_gpio_clear (struct cs5535_gpio_chip*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int) ; 
 struct cs5535_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int mask ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int chip_gpio_request(struct gpio_chip *c, unsigned offset)
{
	struct cs5535_gpio_chip *chip = gpiochip_get_data(c);
	unsigned long flags;

	spin_lock_irqsave(&chip->lock, flags);

	/* check if this pin is available */
	if ((mask & (1 << offset)) == 0) {
		dev_info(&chip->pdev->dev,
			"pin %u is not available (check mask)\n", offset);
		spin_unlock_irqrestore(&chip->lock, flags);
		return -EINVAL;
	}

	/* disable output aux 1 & 2 on this pin */
	__cs5535_gpio_clear(chip, offset, GPIO_OUTPUT_AUX1);
	__cs5535_gpio_clear(chip, offset, GPIO_OUTPUT_AUX2);

	/* disable input aux 1 on this pin */
	__cs5535_gpio_clear(chip, offset, GPIO_INPUT_AUX1);

	spin_unlock_irqrestore(&chip->lock, flags);

	return 0;
}