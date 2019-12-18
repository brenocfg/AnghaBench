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
struct temac_option {int opt; int m_or; int /*<<< orphan*/  reg; } ;
struct temac_local {int options; int /*<<< orphan*/  indirect_lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct temac_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int temac_indirect_in32_locked (struct temac_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  temac_indirect_out32_locked (struct temac_local*,int /*<<< orphan*/ ,int) ; 
 struct temac_option* temac_options ; 

__attribute__((used)) static u32 temac_setoptions(struct net_device *ndev, u32 options)
{
	struct temac_local *lp = netdev_priv(ndev);
	struct temac_option *tp = &temac_options[0];
	int reg;
	unsigned long flags;

	spin_lock_irqsave(lp->indirect_lock, flags);
	while (tp->opt) {
		reg = temac_indirect_in32_locked(lp, tp->reg) & ~tp->m_or;
		if (options & tp->opt) {
			reg |= tp->m_or;
			temac_indirect_out32_locked(lp, tp->reg, reg);
		}
		tp++;
	}
	spin_unlock_irqrestore(lp->indirect_lock, flags);
	lp->options |= options;

	return 0;
}