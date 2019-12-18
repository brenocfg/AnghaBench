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
struct ftmac100 {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ FTMAC100_OFFSET_PHYCR ; 
 scalar_t__ FTMAC100_OFFSET_PHYWDATA ; 
 unsigned int FTMAC100_PHYCR_MIIWR ; 
 unsigned int FTMAC100_PHYCR_PHYAD (int) ; 
 unsigned int FTMAC100_PHYCR_REGAD (int) ; 
 int FTMAC100_PHYWDATA_MIIWDATA (int) ; 
 unsigned int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct ftmac100* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ftmac100_mdio_write(struct net_device *netdev, int phy_id, int reg,
				int data)
{
	struct ftmac100 *priv = netdev_priv(netdev);
	unsigned int phycr;
	int i;

	phycr = FTMAC100_PHYCR_PHYAD(phy_id) |
		FTMAC100_PHYCR_REGAD(reg) |
		FTMAC100_PHYCR_MIIWR;

	data = FTMAC100_PHYWDATA_MIIWDATA(data);

	iowrite32(data, priv->base + FTMAC100_OFFSET_PHYWDATA);
	iowrite32(phycr, priv->base + FTMAC100_OFFSET_PHYCR);

	for (i = 0; i < 10; i++) {
		phycr = ioread32(priv->base + FTMAC100_OFFSET_PHYCR);

		if ((phycr & FTMAC100_PHYCR_MIIWR) == 0)
			return;

		udelay(100);
	}

	netdev_err(netdev, "mdio write timed out\n");
}