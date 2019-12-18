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
struct TYPE_2__ {int /*<<< orphan*/  p; } ;
struct inf_hw {int /*<<< orphan*/  lock; TYPE_1__ cfg; int /*<<< orphan*/  ipac; int /*<<< orphan*/  irqcnt; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int PITA_INT0_STATUS ; 
 int /*<<< orphan*/  irqloops ; 
 int /*<<< orphan*/  mISDNipac_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t
diva20x_irq(int intno, void *dev_id)
{
	struct inf_hw *hw = dev_id;
	u8 val;

	spin_lock(&hw->lock);
	val = readb(hw->cfg.p);
	if (!(val & PITA_INT0_STATUS)) { /* for us or shared ? */
		spin_unlock(&hw->lock);
		return IRQ_NONE; /* shared */
	}
	hw->irqcnt++;
	mISDNipac_irq(&hw->ipac, irqloops);
	writeb(PITA_INT0_STATUS, hw->cfg.p); /* ACK PITA INT0 */
	spin_unlock(&hw->lock);
	return IRQ_HANDLED;
}