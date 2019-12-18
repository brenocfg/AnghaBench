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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ethtool_regs {int len; int /*<<< orphan*/  version; } ;
struct emac_adapter {scalar_t__ base; } ;

/* Variables and functions */
 int EMAC_MAX_REG_SIZE ; 
 int /*<<< orphan*/  EMAC_REGS_VERSION ; 
 scalar_t__* emac_regs ; 
 struct emac_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static void emac_get_regs(struct net_device *netdev,
			  struct ethtool_regs *regs, void *buff)
{
	struct emac_adapter *adpt = netdev_priv(netdev);
	u32 *val = buff;
	unsigned int i;

	regs->version = EMAC_REGS_VERSION;
	regs->len = EMAC_MAX_REG_SIZE * sizeof(u32);

	for (i = 0; i < EMAC_MAX_REG_SIZE; i++)
		val[i] = readl(adpt->base + emac_regs[i]);
}