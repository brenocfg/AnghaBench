#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ioh_gpio {size_t ch; int /*<<< orphan*/  spinlock; TYPE_2__* reg; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_4__ {TYPE_1__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  po; int /*<<< orphan*/  pm; } ;

/* Variables and functions */
 struct ioh_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int* num_ports ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ioh_gpio_direction_output(struct gpio_chip *gpio, unsigned nr,
				     int val)
{
	struct ioh_gpio *chip =	gpiochip_get_data(gpio);
	u32 pm;
	u32 reg_val;
	unsigned long flags;

	spin_lock_irqsave(&chip->spinlock, flags);
	pm = ioread32(&chip->reg->regs[chip->ch].pm) &
					((1 << num_ports[chip->ch]) - 1);
	pm |= (1 << nr);
	iowrite32(pm, &chip->reg->regs[chip->ch].pm);

	reg_val = ioread32(&chip->reg->regs[chip->ch].po);
	if (val)
		reg_val |= (1 << nr);
	else
		reg_val &= ~(1 << nr);
	iowrite32(reg_val, &chip->reg->regs[chip->ch].po);

	spin_unlock_irqrestore(&chip->spinlock, flags);

	return 0;
}