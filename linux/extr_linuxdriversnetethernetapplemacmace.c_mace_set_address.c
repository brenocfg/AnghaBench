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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct mace_data {struct mace* mace; } ;
struct mace {int /*<<< orphan*/  maccc; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mace_set_address (struct net_device*,void*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct mace_data* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mace_set_address(struct net_device *dev, void *addr)
{
	struct mace_data *mp = netdev_priv(dev);
	volatile struct mace *mb = mp->mace;
	unsigned long flags;
	u8 maccc;

	local_irq_save(flags);

	maccc = mb->maccc;

	__mace_set_address(dev, addr);

	mb->maccc = maccc;

	local_irq_restore(flags);

	return 0;
}