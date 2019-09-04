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
struct scoop_dev {int /*<<< orphan*/  scoop_lock; scalar_t__ base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ SCOOP_GPCR ; 
 struct scoop_dev* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned short ioread16 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite16 (unsigned short,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int scoop_gpio_direction_input(struct gpio_chip *chip,
			unsigned offset)
{
	struct scoop_dev *sdev = gpiochip_get_data(chip);
	unsigned long flags;
	unsigned short gpcr;

	spin_lock_irqsave(&sdev->scoop_lock, flags);

	gpcr = ioread16(sdev->base + SCOOP_GPCR);
	gpcr &= ~(1 << (offset + 1));
	iowrite16(gpcr, sdev->base + SCOOP_GPCR);

	spin_unlock_irqrestore(&sdev->scoop_lock, flags);

	return 0;
}