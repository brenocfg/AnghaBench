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
struct net_device {int dummy; } ;
struct emac_board_info {scalar_t__ speed; scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ EMAC_MAC_SUPP_REG ; 
 scalar_t__ SPEED_100 ; 
 struct emac_board_info* netdev_priv (struct net_device*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void emac_update_speed(struct net_device *dev)
{
	struct emac_board_info *db = netdev_priv(dev);
	unsigned int reg_val;

	/* set EMAC SPEED, depend on PHY  */
	reg_val = readl(db->membase + EMAC_MAC_SUPP_REG);
	reg_val &= ~(0x1 << 8);
	if (db->speed == SPEED_100)
		reg_val |= 1 << 8;
	writel(reg_val, db->membase + EMAC_MAC_SUPP_REG);
}