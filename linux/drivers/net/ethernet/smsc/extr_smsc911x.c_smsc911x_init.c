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
struct TYPE_2__ {int flags; } ;
struct smsc911x_data {int generation; unsigned int idrev; int /*<<< orphan*/  napi; int /*<<< orphan*/  mac_lock; TYPE_1__ config; int /*<<< orphan*/ * ioaddr; int /*<<< orphan*/  dev_lock; } ;
struct net_device {int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  flags; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYTE_TEST ; 
 int ENODEV ; 
 int /*<<< orphan*/  ID_REV ; 
 int /*<<< orphan*/  IFF_MULTICAST ; 
#define  LAN89218 141 
#define  LAN9115 140 
#define  LAN9116 139 
#define  LAN9117 138 
#define  LAN9118 137 
#define  LAN9210 136 
#define  LAN9211 135 
#define  LAN9215 134 
#define  LAN9216 133 
#define  LAN9217 132 
#define  LAN9218 131 
#define  LAN9220 130 
#define  LAN9221 129 
#define  LAN9250 128 
 int /*<<< orphan*/  PMT_CTRL ; 
 unsigned int PMT_CTRL_READY_ ; 
 int SMSC911X_SAVE_MAC_ADDRESS ; 
 int /*<<< orphan*/  SMSC_NAPI_WEIGHT ; 
 int /*<<< orphan*/  SMSC_TRACE (struct smsc911x_data*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SMSC_WARN (struct smsc911x_data*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  WORD_SWAP ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct smsc911x_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  smsc911x_ethtool_ops ; 
 int /*<<< orphan*/  smsc911x_netdev_ops ; 
 scalar_t__ smsc911x_phy_reset (struct smsc911x_data*) ; 
 int /*<<< orphan*/  smsc911x_poll ; 
 int /*<<< orphan*/  smsc911x_read_mac_address (struct net_device*) ; 
 unsigned int smsc911x_reg_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_reg_write (struct smsc911x_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ smsc911x_soft_reset (struct smsc911x_data*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 unsigned int swahw32 (unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int smsc911x_init(struct net_device *dev)
{
	struct smsc911x_data *pdata = netdev_priv(dev);
	unsigned int byte_test, mask;
	unsigned int to = 100;

	SMSC_TRACE(pdata, probe, "Driver Parameters:");
	SMSC_TRACE(pdata, probe, "LAN base: 0x%08lX",
		   (unsigned long)pdata->ioaddr);
	SMSC_TRACE(pdata, probe, "IRQ: %d", dev->irq);
	SMSC_TRACE(pdata, probe, "PHY will be autodetected.");

	spin_lock_init(&pdata->dev_lock);
	spin_lock_init(&pdata->mac_lock);

	if (pdata->ioaddr == NULL) {
		SMSC_WARN(pdata, probe, "pdata->ioaddr: 0x00000000");
		return -ENODEV;
	}

	/*
	 * poll the READY bit in PMT_CTRL. Any other access to the device is
	 * forbidden while this bit isn't set. Try for 100ms
	 *
	 * Note that this test is done before the WORD_SWAP register is
	 * programmed. So in some configurations the READY bit is at 16 before
	 * WORD_SWAP is written to. This issue is worked around by waiting
	 * until either bit 0 or bit 16 gets set in PMT_CTRL.
	 *
	 * SMSC has confirmed that checking bit 16 (marked as reserved in
	 * the datasheet) is fine since these bits "will either never be set
	 * or can only go high after READY does (so also indicate the device
	 * is ready)".
	 */

	mask = PMT_CTRL_READY_ | swahw32(PMT_CTRL_READY_);
	while (!(smsc911x_reg_read(pdata, PMT_CTRL) & mask) && --to)
		udelay(1000);

	if (to == 0) {
		netdev_err(dev, "Device not READY in 100ms aborting\n");
		return -ENODEV;
	}

	/* Check byte ordering */
	byte_test = smsc911x_reg_read(pdata, BYTE_TEST);
	SMSC_TRACE(pdata, probe, "BYTE_TEST: 0x%08X", byte_test);
	if (byte_test == 0x43218765) {
		SMSC_TRACE(pdata, probe, "BYTE_TEST looks swapped, "
			   "applying WORD_SWAP");
		smsc911x_reg_write(pdata, WORD_SWAP, 0xffffffff);

		/* 1 dummy read of BYTE_TEST is needed after a write to
		 * WORD_SWAP before its contents are valid */
		byte_test = smsc911x_reg_read(pdata, BYTE_TEST);

		byte_test = smsc911x_reg_read(pdata, BYTE_TEST);
	}

	if (byte_test != 0x87654321) {
		SMSC_WARN(pdata, drv, "BYTE_TEST: 0x%08X", byte_test);
		if (((byte_test >> 16) & 0xFFFF) == (byte_test & 0xFFFF)) {
			SMSC_WARN(pdata, probe,
				  "top 16 bits equal to bottom 16 bits");
			SMSC_TRACE(pdata, probe,
				   "This may mean the chip is set "
				   "for 32 bit while the bus is reading 16 bit");
		}
		return -ENODEV;
	}

	/* Default generation to zero (all workarounds apply) */
	pdata->generation = 0;

	pdata->idrev = smsc911x_reg_read(pdata, ID_REV);
	switch (pdata->idrev & 0xFFFF0000) {
	case LAN9118:
	case LAN9117:
	case LAN9116:
	case LAN9115:
	case LAN89218:
		/* LAN911[5678] family */
		pdata->generation = pdata->idrev & 0x0000FFFF;
		break;

	case LAN9218:
	case LAN9217:
	case LAN9216:
	case LAN9215:
		/* LAN921[5678] family */
		pdata->generation = 3;
		break;

	case LAN9210:
	case LAN9211:
	case LAN9220:
	case LAN9221:
	case LAN9250:
		/* LAN9210/LAN9211/LAN9220/LAN9221/LAN9250 */
		pdata->generation = 4;
		break;

	default:
		SMSC_WARN(pdata, probe, "LAN911x not identified, idrev: 0x%08X",
			  pdata->idrev);
		return -ENODEV;
	}

	SMSC_TRACE(pdata, probe,
		   "LAN911x identified, idrev: 0x%08X, generation: %d",
		   pdata->idrev, pdata->generation);

	if (pdata->generation == 0)
		SMSC_WARN(pdata, probe,
			  "This driver is not intended for this chip revision");

	/* workaround for platforms without an eeprom, where the mac address
	 * is stored elsewhere and set by the bootloader.  This saves the
	 * mac address before resetting the device */
	if (pdata->config.flags & SMSC911X_SAVE_MAC_ADDRESS) {
		spin_lock_irq(&pdata->mac_lock);
		smsc911x_read_mac_address(dev);
		spin_unlock_irq(&pdata->mac_lock);
	}

	/* Reset the LAN911x */
	if (smsc911x_phy_reset(pdata) || smsc911x_soft_reset(pdata))
		return -ENODEV;

	dev->flags |= IFF_MULTICAST;
	netif_napi_add(dev, &pdata->napi, smsc911x_poll, SMSC_NAPI_WEIGHT);
	dev->netdev_ops = &smsc911x_netdev_ops;
	dev->ethtool_ops = &smsc911x_ethtool_ops;

	return 0;
}