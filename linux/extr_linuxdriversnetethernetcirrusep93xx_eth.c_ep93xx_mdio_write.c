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
struct ep93xx_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_MIICMD ; 
 int REG_MIICMD_WRITE ; 
 int /*<<< orphan*/  REG_MIIDATA ; 
 int /*<<< orphan*/  REG_MIISTS ; 
 int REG_MIISTS_BUSY ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct ep93xx_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int rdl (struct ep93xx_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrl (struct ep93xx_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ep93xx_mdio_write(struct net_device *dev, int phy_id, int reg, int data)
{
	struct ep93xx_priv *ep = netdev_priv(dev);
	int i;

	wrl(ep, REG_MIIDATA, data);
	wrl(ep, REG_MIICMD, REG_MIICMD_WRITE | (phy_id << 5) | reg);

	for (i = 0; i < 10; i++) {
		if ((rdl(ep, REG_MIISTS) & REG_MIISTS_BUSY) == 0)
			break;
		msleep(1);
	}

	if (i == 10)
		pr_info("mdio write timed out\n");
}