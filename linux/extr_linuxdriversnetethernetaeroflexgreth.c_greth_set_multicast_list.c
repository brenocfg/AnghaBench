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
struct net_device {int flags; } ;
struct greth_regs {int /*<<< orphan*/  control; int /*<<< orphan*/  hash_lsb; int /*<<< orphan*/  hash_msb; } ;
struct greth_private {scalar_t__ multicast; struct greth_regs* regs; } ;

/* Variables and functions */
 int GRETH_CTRL_MCEN ; 
 int GRETH_CTRL_PR ; 
 int GRETH_REGLOAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GRETH_REGSAVE (int /*<<< orphan*/ ,int) ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  greth_set_hash_filter (struct net_device*) ; 
 scalar_t__ netdev_mc_empty (struct net_device*) ; 
 struct greth_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void greth_set_multicast_list(struct net_device *dev)
{
	int cfg;
	struct greth_private *greth = netdev_priv(dev);
	struct greth_regs *regs = greth->regs;

	cfg = GRETH_REGLOAD(regs->control);
	if (dev->flags & IFF_PROMISC)
		cfg |= GRETH_CTRL_PR;
	else
		cfg &= ~GRETH_CTRL_PR;

	if (greth->multicast) {
		if (dev->flags & IFF_ALLMULTI) {
			GRETH_REGSAVE(regs->hash_msb, -1);
			GRETH_REGSAVE(regs->hash_lsb, -1);
			cfg |= GRETH_CTRL_MCEN;
			GRETH_REGSAVE(regs->control, cfg);
			return;
		}

		if (netdev_mc_empty(dev)) {
			cfg &= ~GRETH_CTRL_MCEN;
			GRETH_REGSAVE(regs->control, cfg);
			return;
		}

		/* Setup multicast filter */
		greth_set_hash_filter(dev);
		cfg |= GRETH_CTRL_MCEN;
	}
	GRETH_REGSAVE(regs->control, cfg);
}