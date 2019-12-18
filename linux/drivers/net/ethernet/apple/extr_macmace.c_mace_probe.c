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
typedef  unsigned char u8 ;
typedef  scalar_t__ u32 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {unsigned char* dev_addr; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  irq; scalar_t__ base_addr; } ;
struct mace_data {int chipid; TYPE_1__* mace; int /*<<< orphan*/  dma_intr; int /*<<< orphan*/ * device; } ;
struct TYPE_2__ {int chipid_hi; int chipid_lo; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQ_MAC_MACE ; 
 int /*<<< orphan*/  IRQ_MAC_MACE_DMA ; 
 TYPE_1__* MACE_BASE ; 
 unsigned char* MACE_PROM ; 
 int /*<<< orphan*/  PRIV_BYTES ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TX_TIMEOUT ; 
 struct net_device* alloc_etherdev (int /*<<< orphan*/ ) ; 
 unsigned char bitrev8 (unsigned char) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mace_netdev_ops ; 
 struct mace_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned char*,int) ; 
 int register_netdev (struct net_device*) ; 

__attribute__((used)) static int mace_probe(struct platform_device *pdev)
{
	int j;
	struct mace_data *mp;
	unsigned char *addr;
	struct net_device *dev;
	unsigned char checksum = 0;
	int err;

	dev = alloc_etherdev(PRIV_BYTES);
	if (!dev)
		return -ENOMEM;

	mp = netdev_priv(dev);

	mp->device = &pdev->dev;
	platform_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	dev->base_addr = (u32)MACE_BASE;
	mp->mace = MACE_BASE;

	dev->irq = IRQ_MAC_MACE;
	mp->dma_intr = IRQ_MAC_MACE_DMA;

	mp->chipid = mp->mace->chipid_hi << 8 | mp->mace->chipid_lo;

	/*
	 * The PROM contains 8 bytes which total 0xFF when XOR'd
	 * together. Due to the usual peculiar apple brain damage
	 * the bytes are spaced out in a strange boundary and the
	 * bits are reversed.
	 */

	addr = MACE_PROM;

	for (j = 0; j < 6; ++j) {
		u8 v = bitrev8(addr[j<<4]);
		checksum ^= v;
		dev->dev_addr[j] = v;
	}
	for (; j < 8; ++j) {
		checksum ^= bitrev8(addr[j<<4]);
	}

	if (checksum != 0xFF) {
		free_netdev(dev);
		return -ENODEV;
	}

	dev->netdev_ops		= &mace_netdev_ops;
	dev->watchdog_timeo	= TX_TIMEOUT;

	pr_info("Onboard MACE, hardware address %pM, chip revision 0x%04X\n",
		dev->dev_addr, mp->chipid);

	err = register_netdev(dev);
	if (!err)
		return 0;

	free_netdev(dev);
	return err;
}