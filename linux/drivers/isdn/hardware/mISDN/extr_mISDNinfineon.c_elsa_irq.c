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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ start; } ;
struct inf_hw {int /*<<< orphan*/  lock; int /*<<< orphan*/  ipac; int /*<<< orphan*/  irqcnt; TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ ELSA_IRQ_ADDR ; 
 int ELSA_IRQ_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  irqloops ; 
 int /*<<< orphan*/  mISDNipac_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
elsa_irq(int intno, void *dev_id)
{
	struct inf_hw *hw = dev_id;
	u8 val;

	spin_lock(&hw->lock);
	val = inb((u32)hw->cfg.start + ELSA_IRQ_ADDR);
	if (!(val & ELSA_IRQ_MASK)) {
		spin_unlock(&hw->lock);
		return IRQ_NONE; /* shared */
	}
	hw->irqcnt++;
	mISDNipac_irq(&hw->ipac, irqloops);
	spin_unlock(&hw->lock);
	return IRQ_HANDLED;
}