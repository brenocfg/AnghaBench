#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct tpci200_board {int /*<<< orphan*/  number; TYPE_4__* info; TYPE_2__* slots; } ;
struct slot_irq {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_8__ {TYPE_3__* pdev; TYPE_1__* interface_regs; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;
struct TYPE_5__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int TPCI200_A_INT0 ; 
 int TPCI200_A_INT1 ; 
 int TPCI200_NB_SLOT ; 
 int TPCI200_SLOT_INT_MASK ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int ioread16 (int /*<<< orphan*/ *) ; 
 struct slot_irq* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  tpci200_disable_irq (struct tpci200_board*,int) ; 
 int /*<<< orphan*/  tpci200_slot_irq (struct slot_irq*) ; 

__attribute__((used)) static irqreturn_t tpci200_interrupt(int irq, void *dev_id)
{
	struct tpci200_board *tpci200 = (struct tpci200_board *) dev_id;
	struct slot_irq *slot_irq;
	irqreturn_t ret;
	u16 status_reg;
	int i;

	/* Read status register */
	status_reg = ioread16(&tpci200->info->interface_regs->status);

	/* Did we cause the interrupt? */
	if (!(status_reg & TPCI200_SLOT_INT_MASK))
		return IRQ_NONE;

	/* callback to the IRQ handler for the corresponding slot */
	rcu_read_lock();
	for (i = 0; i < TPCI200_NB_SLOT; i++) {
		if (!(status_reg & ((TPCI200_A_INT0 | TPCI200_A_INT1) << (2 * i))))
			continue;
		slot_irq = rcu_dereference(tpci200->slots[i].irq);
		ret = tpci200_slot_irq(slot_irq);
		if (ret == -ENODEV) {
			dev_info(&tpci200->info->pdev->dev,
				 "No registered ISR for slot [%d:%d]!. IRQ will be disabled.\n",
				 tpci200->number, i);
			tpci200_disable_irq(tpci200, i);
		}
	}
	rcu_read_unlock();

	return IRQ_HANDLED;
}