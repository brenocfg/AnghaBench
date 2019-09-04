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
typedef  int u_char ;
typedef  int /*<<< orphan*/  u8 ;
struct pcmcia_device {int io_lines; char** prod_id; int /*<<< orphan*/  dev; TYPE_1__** resource; int /*<<< orphan*/  irq; struct net_device* priv; } ;
struct net_device {unsigned int base_addr; scalar_t__ dev_addr; int /*<<< orphan*/  irq; } ;
struct el3_private {int default_media; int autoselect; int phys; int advertising; int /*<<< orphan*/  media; } ;
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int start; } ;

/* Variables and functions */
 int Autoselect ; 
 int /*<<< orphan*/  EL3WINDOW (int) ; 
 int ENODEV ; 
 int Ram_size ; 
 int Ram_split ; 
 int Ram_split_shift ; 
 scalar_t__ RunnerRdCtrl ; 
 int /*<<< orphan*/  RxReset ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TxReset ; 
 scalar_t__ Wn3_Config ; 
 scalar_t__ Wn3_Options ; 
 int Xcvr ; 
 int Xcvr_shift ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  el3_interrupt ; 
 scalar_t__ full_duplex ; 
 int /*<<< orphan*/  htons (int) ; 
 int inb (unsigned int) ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int mdio_read (unsigned int,int,int) ; 
 int /*<<< orphan*/  mdio_sync (unsigned int,int) ; 
 int /*<<< orphan*/  mdio_write (unsigned int,int,int,int) ; 
 int /*<<< orphan*/  media_check ; 
 int mii_preamble_required ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 struct el3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 size_t pcmcia_get_tuple (struct pcmcia_device*,int,int /*<<< orphan*/ **) ; 
 int pcmcia_request_io (struct pcmcia_device*) ; 
 int pcmcia_request_irq (struct pcmcia_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  pr_notice (char*,...) ; 
 int /*<<< orphan*/ * ram_split ; 
 int read_eeprom (unsigned int,int) ; 
 scalar_t__ register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  tc574_release (struct pcmcia_device*) ; 
 int /*<<< orphan*/  tc574_wait_for_completion (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tc574_config(struct pcmcia_device *link)
{
	struct net_device *dev = link->priv;
	struct el3_private *lp = netdev_priv(dev);
	int ret, i, j;
	unsigned int ioaddr;
	__be16 *phys_addr;
	char *cardname;
	__u32 config;
	u8 *buf;
	size_t len;

	phys_addr = (__be16 *)dev->dev_addr;

	dev_dbg(&link->dev, "3c574_config()\n");

	link->io_lines = 16;

	for (i = j = 0; j < 0x400; j += 0x20) {
		link->resource[0]->start = j ^ 0x300;
		i = pcmcia_request_io(link);
		if (i == 0)
			break;
	}
	if (i != 0)
		goto failed;

	ret = pcmcia_request_irq(link, el3_interrupt);
	if (ret)
		goto failed;

	ret = pcmcia_enable_device(link);
	if (ret)
		goto failed;

	dev->irq = link->irq;
	dev->base_addr = link->resource[0]->start;

	ioaddr = dev->base_addr;

	/* The 3c574 normally uses an EEPROM for configuration info, including
	   the hardware address.  The future products may include a modem chip
	   and put the address in the CIS. */

	len = pcmcia_get_tuple(link, 0x88, &buf);
	if (buf && len >= 6) {
		for (i = 0; i < 3; i++)
			phys_addr[i] = htons(le16_to_cpu(buf[i * 2]));
		kfree(buf);
	} else {
		kfree(buf); /* 0 < len < 6 */
		EL3WINDOW(0);
		for (i = 0; i < 3; i++)
			phys_addr[i] = htons(read_eeprom(ioaddr, i + 10));
		if (phys_addr[0] == htons(0x6060)) {
			pr_notice("IO port conflict at 0x%03lx-0x%03lx\n",
				  dev->base_addr, dev->base_addr+15);
			goto failed;
		}
	}
	if (link->prod_id[1])
		cardname = link->prod_id[1];
	else
		cardname = "3Com 3c574";

	{
		u_char mcr;
		outw(2<<11, ioaddr + RunnerRdCtrl);
		mcr = inb(ioaddr + 2);
		outw(0<<11, ioaddr + RunnerRdCtrl);
		pr_info("  ASIC rev %d,", mcr>>3);
		EL3WINDOW(3);
		config = inl(ioaddr + Wn3_Config);
		lp->default_media = (config & Xcvr) >> Xcvr_shift;
		lp->autoselect = config & Autoselect ? 1 : 0;
	}

	timer_setup(&lp->media, media_check, 0);

	{
		int phy;
		
		/* Roadrunner only: Turn on the MII transceiver */
		outw(0x8040, ioaddr + Wn3_Options);
		mdelay(1);
		outw(0xc040, ioaddr + Wn3_Options);
		tc574_wait_for_completion(dev, TxReset);
		tc574_wait_for_completion(dev, RxReset);
		mdelay(1);
		outw(0x8040, ioaddr + Wn3_Options);
		
		EL3WINDOW(4);
		for (phy = 1; phy <= 32; phy++) {
			int mii_status;
			mdio_sync(ioaddr, 32);
			mii_status = mdio_read(ioaddr, phy & 0x1f, 1);
			if (mii_status != 0xffff) {
				lp->phys = phy & 0x1f;
				dev_dbg(&link->dev, "  MII transceiver at "
					"index %d, status %x.\n",
					  phy, mii_status);
				if ((mii_status & 0x0040) == 0)
					mii_preamble_required = 1;
				break;
			}
		}
		if (phy > 32) {
			pr_notice("  No MII transceivers found!\n");
			goto failed;
		}
		i = mdio_read(ioaddr, lp->phys, 16) | 0x40;
		mdio_write(ioaddr, lp->phys, 16, i);
		lp->advertising = mdio_read(ioaddr, lp->phys, 4);
		if (full_duplex) {
			/* Only advertise the FD media types. */
			lp->advertising &= ~0x02a0;
			mdio_write(ioaddr, lp->phys, 4, lp->advertising);
		}
	}

	SET_NETDEV_DEV(dev, &link->dev);

	if (register_netdev(dev) != 0) {
		pr_notice("register_netdev() failed\n");
		goto failed;
	}

	netdev_info(dev, "%s at io %#3lx, irq %d, hw_addr %pM\n",
		    cardname, dev->base_addr, dev->irq, dev->dev_addr);
	netdev_info(dev, " %dK FIFO split %s Rx:Tx, %sMII interface.\n",
		    8 << (config & Ram_size),
		    ram_split[(config & Ram_split) >> Ram_split_shift],
		    config & Autoselect ? "autoselect " : "");

	return 0;

failed:
	tc574_release(link);
	return -ENODEV;

}