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
typedef  int u8 ;
struct tc6393xb {int irq_base; int /*<<< orphan*/  lock; scalar_t__ scr; } ;
struct irq_data {int irq; } ;

/* Variables and functions */
 scalar_t__ SCR_IMR ; 
 struct tc6393xb* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int tmio_ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  tmio_iowrite8 (int,scalar_t__) ; 

__attribute__((used)) static void tc6393xb_irq_unmask(struct irq_data *data)
{
	struct tc6393xb *tc6393xb = irq_data_get_irq_chip_data(data);
	unsigned long flags;
	u8 imr;

	raw_spin_lock_irqsave(&tc6393xb->lock, flags);
	imr = tmio_ioread8(tc6393xb->scr + SCR_IMR);
	imr &= ~(1 << (data->irq - tc6393xb->irq_base));
	tmio_iowrite8(imr, tc6393xb->scr + SCR_IMR);
	raw_spin_unlock_irqrestore(&tc6393xb->lock, flags);
}