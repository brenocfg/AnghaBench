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
struct irq_data {int irq; } ;
struct irq_chip_generic {struct ioh_gpio* private; } ;
struct ioh_gpio {size_t ch; int irq_base; int /*<<< orphan*/  spinlock; TYPE_2__* reg; } ;
struct TYPE_4__ {TYPE_1__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  ien; } ;

/* Variables and functions */
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ioh_irq_disable(struct irq_data *d)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	struct ioh_gpio *chip = gc->private;
	unsigned long flags;
	u32 ien;

	spin_lock_irqsave(&chip->spinlock, flags);
	ien = ioread32(&chip->reg->regs[chip->ch].ien);
	ien &= ~(1 << (d->irq - chip->irq_base));
	iowrite32(ien, &chip->reg->regs[chip->ch].ien);
	spin_unlock_irqrestore(&chip->spinlock, flags);
}