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
typedef  int u32 ;
struct pt_gpio_chip {scalar_t__ reg_base; } ;
struct gpio_chip {int /*<<< orphan*/  bgpio_lock; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int EINVAL ; 
 scalar_t__ PT_SYNC_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct pt_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int pt_gpio_request(struct gpio_chip *gc, unsigned offset)
{
	struct pt_gpio_chip *pt_gpio = gpiochip_get_data(gc);
	unsigned long flags;
	u32 using_pins;

	dev_dbg(gc->parent, "pt_gpio_request offset=%x\n", offset);

	spin_lock_irqsave(&gc->bgpio_lock, flags);

	using_pins = readl(pt_gpio->reg_base + PT_SYNC_REG);
	if (using_pins & BIT(offset)) {
		dev_warn(gc->parent, "PT GPIO pin %x reconfigured\n",
			 offset);
		spin_unlock_irqrestore(&gc->bgpio_lock, flags);
		return -EINVAL;
	}

	writel(using_pins | BIT(offset), pt_gpio->reg_base + PT_SYNC_REG);

	spin_unlock_irqrestore(&gc->bgpio_lock, flags);

	return 0;
}