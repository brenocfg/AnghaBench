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
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_2__ {int (* init ) (TYPE_1__*) ;} ;
struct sfax_hw {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; int /*<<< orphan*/  irqcnt; int /*<<< orphan*/  lock; TYPE_1__ isac; } ;

/* Variables and functions */
 int DEBUG_HW ; 
 int EIO ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  ISAC_CMDR ; 
 int /*<<< orphan*/  WriteISAC_IND (struct sfax_hw*,int /*<<< orphan*/ ,int) ; 
 int debug ; 
 int /*<<< orphan*/  enable_hwirq (struct sfax_hw*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sfax_hw*) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sfax_hw*) ; 
 int /*<<< orphan*/  speedfax_irq ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*) ; 

__attribute__((used)) static int
init_card(struct sfax_hw *sf)
{
	int	ret, cnt = 3;
	u_long	flags;

	ret = request_irq(sf->irq, speedfax_irq, IRQF_SHARED, sf->name, sf);
	if (ret) {
		pr_info("%s: couldn't get interrupt %d\n", sf->name, sf->irq);
		return ret;
	}
	while (cnt--) {
		spin_lock_irqsave(&sf->lock, flags);
		ret = sf->isac.init(&sf->isac);
		if (ret) {
			spin_unlock_irqrestore(&sf->lock, flags);
			pr_info("%s: ISAC init failed with %d\n",
				sf->name, ret);
			break;
		}
		enable_hwirq(sf);
		/* RESET Receiver and Transmitter */
		WriteISAC_IND(sf, ISAC_CMDR, 0x41);
		spin_unlock_irqrestore(&sf->lock, flags);
		msleep_interruptible(10);
		if (debug & DEBUG_HW)
			pr_notice("%s: IRQ %d count %d\n", sf->name,
				  sf->irq, sf->irqcnt);
		if (!sf->irqcnt) {
			pr_info("%s: IRQ(%d) got no requests during init %d\n",
				sf->name, sf->irq, 3 - cnt);
		} else
			return 0;
	}
	free_irq(sf->irq, sf);
	return -EIO;
}