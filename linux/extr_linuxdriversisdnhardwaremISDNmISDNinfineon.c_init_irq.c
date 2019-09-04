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
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_4__ {int (* init ) (TYPE_2__*) ;} ;
struct inf_hw {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; int /*<<< orphan*/  irqcnt; int /*<<< orphan*/  lock; TYPE_2__ ipac; TYPE_1__* ci; } ;
struct TYPE_3__ {int /*<<< orphan*/  irqfunc; } ;

/* Variables and functions */
 int DEBUG_HW ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int debug ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct inf_hw*) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inf_hw*) ; 
 int /*<<< orphan*/  reset_inf (struct inf_hw*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*) ; 

__attribute__((used)) static int
init_irq(struct inf_hw *hw)
{
	int	ret, cnt = 3;
	u_long	flags;

	if (!hw->ci->irqfunc)
		return -EINVAL;
	ret = request_irq(hw->irq, hw->ci->irqfunc, IRQF_SHARED, hw->name, hw);
	if (ret) {
		pr_info("%s: couldn't get interrupt %d\n", hw->name, hw->irq);
		return ret;
	}
	while (cnt--) {
		spin_lock_irqsave(&hw->lock, flags);
		reset_inf(hw);
		ret = hw->ipac.init(&hw->ipac);
		if (ret) {
			spin_unlock_irqrestore(&hw->lock, flags);
			pr_info("%s: ISAC init failed with %d\n",
				hw->name, ret);
			break;
		}
		spin_unlock_irqrestore(&hw->lock, flags);
		msleep_interruptible(10);
		if (debug & DEBUG_HW)
			pr_notice("%s: IRQ %d count %d\n", hw->name,
				  hw->irq, hw->irqcnt);
		if (!hw->irqcnt) {
			pr_info("%s: IRQ(%d) got no requests during init %d\n",
				hw->name, hw->irq, 3 - cnt);
		} else
			return 0;
	}
	free_irq(hw->irq, hw);
	return -EIO;
}