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
typedef  int u_long ;
struct TYPE_2__ {int phy_id; } ;
struct smc_private {int manfid; scalar_t__ cardid; int cfg; TYPE_1__ mii_if; scalar_t__ rx_ovrn; scalar_t__ duplex; } ;
struct pcmcia_device {int manf_id; scalar_t__ card_id; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; struct net_device* priv; } ;
struct net_device {int if_port; unsigned int base_addr; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int CFG_16BIT ; 
 int CFG_AUI_SELECT ; 
 int CFG_IRQ_SEL_0 ; 
 int CFG_IRQ_SEL_1 ; 
 int CFG_MII_SELECT ; 
 int CFG_NO_WAIT ; 
 int CFG_STATIC ; 
 scalar_t__ CONFIG ; 
 int ENODEV ; 
#define  MANFID_MEGAHERTZ 133 
#define  MANFID_MOTOROLA 132 
#define  MANFID_NEW_MEDIA 131 
#define  MANFID_OSITECH 130 
#define  MANFID_PSION 129 
#define  MANFID_SMC 128 
 scalar_t__ MEMCFG ; 
 scalar_t__ MEMINFO ; 
 scalar_t__ PRODID_MEGAHERTZ_EM3288 ; 
 scalar_t__ PRODID_MEGAHERTZ_VARIOUS ; 
 scalar_t__ PRODID_OSITECH_SEVEN ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SMC_SELECT_BANK (int) ; 
 int check_sig (struct pcmcia_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 char** if_names ; 
 int if_port ; 
 int inw (scalar_t__) ; 
 int mdio_read (struct net_device*,int,int) ; 
 int mhz_mfc_config (struct pcmcia_device*) ; 
 int mhz_setup (struct pcmcia_device*) ; 
 int /*<<< orphan*/  mot_config (struct pcmcia_device*) ; 
 int mot_setup (struct pcmcia_device*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int,int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*) ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int osi_config (struct pcmcia_device*) ; 
 int osi_setup (struct pcmcia_device*,int,scalar_t__) ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 int pcmcia_request_irq (struct pcmcia_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*,char*) ; 
 scalar_t__ register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  smc91c92_release (struct pcmcia_device*) ; 
 int smc_config (struct pcmcia_device*) ; 
 int /*<<< orphan*/  smc_interrupt ; 
 int smc_setup (struct pcmcia_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int smc91c92_config(struct pcmcia_device *link)
{
    struct net_device *dev = link->priv;
    struct smc_private *smc = netdev_priv(dev);
    char *name;
    int i, rev, j = 0;
    unsigned int ioaddr;
    u_long mir;

    dev_dbg(&link->dev, "smc91c92_config\n");

    smc->manfid = link->manf_id;
    smc->cardid = link->card_id;

    if ((smc->manfid == MANFID_OSITECH) &&
	(smc->cardid != PRODID_OSITECH_SEVEN)) {
	i = osi_config(link);
    } else if ((smc->manfid == MANFID_MOTOROLA) ||
	       ((smc->manfid == MANFID_MEGAHERTZ) &&
		((smc->cardid == PRODID_MEGAHERTZ_VARIOUS) ||
		 (smc->cardid == PRODID_MEGAHERTZ_EM3288)))) {
	i = mhz_mfc_config(link);
    } else {
	i = smc_config(link);
    }
    if (i)
	    goto config_failed;

    i = pcmcia_request_irq(link, smc_interrupt);
    if (i)
	    goto config_failed;
    i = pcmcia_enable_device(link);
    if (i)
	    goto config_failed;

    if (smc->manfid == MANFID_MOTOROLA)
	mot_config(link);

    dev->irq = link->irq;

    if ((if_port >= 0) && (if_port <= 2))
	dev->if_port = if_port;
    else
	dev_notice(&link->dev, "invalid if_port requested\n");

    switch (smc->manfid) {
    case MANFID_OSITECH:
    case MANFID_PSION:
	i = osi_setup(link, smc->manfid, smc->cardid); break;
    case MANFID_SMC:
    case MANFID_NEW_MEDIA:
	i = smc_setup(link); break;
    case 0x128: /* For broken Megahertz cards */
    case MANFID_MEGAHERTZ:
	i = mhz_setup(link); break;
    case MANFID_MOTOROLA:
    default: /* get the hw address from EEPROM */
	i = mot_setup(link); break;
    }

    if (i != 0) {
	dev_notice(&link->dev, "Unable to find hardware address.\n");
	goto config_failed;
    }

    smc->duplex = 0;
    smc->rx_ovrn = 0;

    rev = check_sig(link);
    name = "???";
    if (rev > 0)
	switch (rev >> 4) {
	case 3: name = "92"; break;
	case 4: name = ((rev & 15) >= 6) ? "96" : "94"; break;
	case 5: name = "95"; break;
	case 7: name = "100"; break;
	case 8: name = "100-FD"; break;
	case 9: name = "110"; break;
	}

    ioaddr = dev->base_addr;
    if (rev > 0) {
	u_long mcr;
	SMC_SELECT_BANK(0);
	mir = inw(ioaddr + MEMINFO) & 0xff;
	if (mir == 0xff) mir++;
	/* Get scale factor for memory size */
	mcr = ((rev >> 4) > 3) ? inw(ioaddr + MEMCFG) : 0x0200;
	mir *= 128 * (1<<((mcr >> 9) & 7));
	SMC_SELECT_BANK(1);
	smc->cfg = inw(ioaddr + CONFIG) & ~CFG_AUI_SELECT;
	smc->cfg |= CFG_NO_WAIT | CFG_16BIT | CFG_STATIC;
	if (smc->manfid == MANFID_OSITECH)
	    smc->cfg |= CFG_IRQ_SEL_1 | CFG_IRQ_SEL_0;
	if ((rev >> 4) >= 7)
	    smc->cfg |= CFG_MII_SELECT;
    } else
	mir = 0;

    if (smc->cfg & CFG_MII_SELECT) {
	SMC_SELECT_BANK(3);

	for (i = 0; i < 32; i++) {
	    j = mdio_read(dev, i, 1);
	    if ((j != 0) && (j != 0xffff)) break;
	}
	smc->mii_if.phy_id = (i < 32) ? i : -1;

	SMC_SELECT_BANK(0);
    }

    SET_NETDEV_DEV(dev, &link->dev);

    if (register_netdev(dev) != 0) {
	dev_err(&link->dev, "register_netdev() failed\n");
	goto config_undo;
    }

    netdev_info(dev, "smc91c%s rev %d: io %#3lx, irq %d, hw_addr %pM\n",
		name, (rev & 0x0f), dev->base_addr, dev->irq, dev->dev_addr);

    if (rev > 0) {
	if (mir & 0x3ff)
	    netdev_info(dev, "  %lu byte", mir);
	else
	    netdev_info(dev, "  %lu kb", mir>>10);
	pr_cont(" buffer, %s xcvr\n",
		(smc->cfg & CFG_MII_SELECT) ? "MII" : if_names[dev->if_port]);
    }

    if (smc->cfg & CFG_MII_SELECT) {
	if (smc->mii_if.phy_id != -1) {
	    netdev_dbg(dev, "  MII transceiver at index %d, status %x\n",
		       smc->mii_if.phy_id, j);
	} else {
	    netdev_notice(dev, "  No MII transceivers found!\n");
	}
    }
    return 0;

config_undo:
    unregister_netdev(dev);
config_failed:
    smc91c92_release(link);
    free_netdev(dev);
    return -ENODEV;
}