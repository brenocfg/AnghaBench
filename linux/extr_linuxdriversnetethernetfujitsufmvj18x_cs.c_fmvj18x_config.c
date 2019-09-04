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
typedef  void* u_char ;
typedef  void* u8 ;
struct pcmcia_device {int io_lines; int manf_id; int config_base; int config_index; int /*<<< orphan*/  dev; TYPE_1__** resource; int /*<<< orphan*/  irq; int /*<<< orphan*/  card_id; struct net_device* priv; } ;
struct net_device {unsigned int base_addr; void** dev_addr; int /*<<< orphan*/  irq; } ;
struct local_info {int cardtype; } ;
typedef  enum cardtype { ____Placeholder_cardtype } cardtype ;
struct TYPE_2__ {int end; unsigned int start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_0 ; 
 int /*<<< orphan*/  BANK_0U ; 
 int /*<<< orphan*/  CISTPL_FUNCE ; 
 int /*<<< orphan*/  CONFIG0_RST ; 
 int /*<<< orphan*/  CONFIG0_RST_1 ; 
 scalar_t__ CONFIG_0 ; 
 scalar_t__ CONFIG_1 ; 
#define  CONTEC 142 
 int ENODEV ; 
#define  KME 141 
#define  LA501 140 
 int /*<<< orphan*/  MAC_ID ; 
#define  MANFID_CONTEC 139 
#define  MANFID_FUJITSU 138 
#define  MANFID_KME 137 
#define  MANFID_NEC 136 
#define  MANFID_TDK 135 
#define  MANFID_UNGERMANN 134 
#define  MBH10302 133 
#define  MBH10304 132 
#define  NEC 131 
 int /*<<< orphan*/  PRODID_FUJITSU_MBH10302 ; 
 int /*<<< orphan*/  PRODID_FUJITSU_MBH10304 ; 
 int /*<<< orphan*/  PRODID_TDK_GN3410 ; 
 int /*<<< orphan*/  PRODID_TDK_MN3200 ; 
 int /*<<< orphan*/  PRODID_TDK_NP9610 ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
#define  TDK 130 
#define  UNGERMANN 129 
 int /*<<< orphan*/  UNGERMANN_MAC_ID ; 
#define  XXX10304 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fjn_interrupt ; 
 int fmvj18x_get_hwinfo (struct pcmcia_device*,void**) ; 
 int /*<<< orphan*/  fmvj18x_ioprobe ; 
 int /*<<< orphan*/  fmvj18x_release (struct pcmcia_device*) ; 
 int fmvj18x_setup_mfc (struct pcmcia_device*) ; 
 void* inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void**) ; 
 int mfc_try_io_port (struct pcmcia_device*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,char*,char*,unsigned int,int /*<<< orphan*/ ,void**) ; 
 struct local_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 int /*<<< orphan*/  pcmcia_get_mac_from_cis (struct pcmcia_device*,struct net_device*) ; 
 size_t pcmcia_get_tuple (struct pcmcia_device*,int /*<<< orphan*/ ,void***) ; 
 int pcmcia_loop_config (struct pcmcia_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pcmcia_request_io (struct pcmcia_device*) ; 
 int pcmcia_request_irq (struct pcmcia_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 scalar_t__ register_netdev (struct net_device*) ; 
 scalar_t__ resource_size (TYPE_1__*) ; 
 scalar_t__ sram_config ; 
 int ungermann_try_io_port (struct pcmcia_device*) ; 

__attribute__((used)) static int fmvj18x_config(struct pcmcia_device *link)
{
    struct net_device *dev = link->priv;
    struct local_info *lp = netdev_priv(dev);
    int i, ret;
    unsigned int ioaddr;
    enum cardtype cardtype;
    char *card_name = "unknown";
    u8 *buf;
    size_t len;
    u_char buggybuf[32];

    dev_dbg(&link->dev, "fmvj18x_config\n");

    link->io_lines = 5;

    len = pcmcia_get_tuple(link, CISTPL_FUNCE, &buf);
    kfree(buf);

    if (len) {
	/* Yes, I have CISTPL_FUNCE. Let's check CISTPL_MANFID */
	ret = pcmcia_loop_config(link, fmvj18x_ioprobe, NULL);
	if (ret != 0)
		goto failed;

	switch (link->manf_id) {
	case MANFID_TDK:
	    cardtype = TDK;
	    if (link->card_id == PRODID_TDK_GN3410 ||
		link->card_id == PRODID_TDK_NP9610 ||
		link->card_id == PRODID_TDK_MN3200) {
		/* MultiFunction Card */
		link->config_base = 0x800;
		link->config_index = 0x47;
		link->resource[1]->end = 8;
	    }
	    break;
	case MANFID_NEC:
	    cardtype = NEC; /* MultiFunction Card */
	    link->config_base = 0x800;
	    link->config_index = 0x47;
	    link->resource[1]->end = 8;
	    break;
	case MANFID_KME:
	    cardtype = KME; /* MultiFunction Card */
	    link->config_base = 0x800;
	    link->config_index = 0x47;
	    link->resource[1]->end = 8;
	    break;
	case MANFID_CONTEC:
	    cardtype = CONTEC;
	    break;
	case MANFID_FUJITSU:
	    if (link->config_base == 0x0fe0)
		cardtype = MBH10302;
	    else if (link->card_id == PRODID_FUJITSU_MBH10302) 
                /* RATOC REX-5588/9822/4886's PRODID are 0004(=MBH10302),
                   but these are MBH10304 based card. */ 
		cardtype = MBH10304;
	    else if (link->card_id == PRODID_FUJITSU_MBH10304)
		cardtype = MBH10304;
	    else
		cardtype = LA501;
	    break;
	default:
	    cardtype = MBH10304;
	}
    } else {
	/* old type card */
	switch (link->manf_id) {
	case MANFID_FUJITSU:
	    if (link->card_id == PRODID_FUJITSU_MBH10304) {
		cardtype = XXX10304;    /* MBH10304 with buggy CIS */
		link->config_index = 0x20;
	    } else {
		cardtype = MBH10302;    /* NextCom NC5310, etc. */
		link->config_index = 1;
	    }
	    break;
	case MANFID_UNGERMANN:
	    cardtype = UNGERMANN;
	    break;
	default:
	    cardtype = MBH10302;
	    link->config_index = 1;
	}
    }

    if (link->resource[1]->end != 0) {
	ret = mfc_try_io_port(link);
	if (ret != 0) goto failed;
    } else if (cardtype == UNGERMANN) {
	ret = ungermann_try_io_port(link);
	if (ret != 0) goto failed;
    } else { 
	    ret = pcmcia_request_io(link);
	    if (ret)
		    goto failed;
    }
    ret = pcmcia_request_irq(link, fjn_interrupt);
    if (ret)
	    goto failed;
    ret = pcmcia_enable_device(link);
    if (ret)
	    goto failed;

    dev->irq = link->irq;
    dev->base_addr = link->resource[0]->start;

    if (resource_size(link->resource[1]) != 0) {
	ret = fmvj18x_setup_mfc(link);
	if (ret != 0) goto failed;
    }

    ioaddr = dev->base_addr;

    /* Reset controller */
    if (sram_config == 0) 
	outb(CONFIG0_RST, ioaddr + CONFIG_0);
    else
	outb(CONFIG0_RST_1, ioaddr + CONFIG_0);

    /* Power On chip and select bank 0 */
    if (cardtype == MBH10302)
	outb(BANK_0, ioaddr + CONFIG_1);
    else
	outb(BANK_0U, ioaddr + CONFIG_1);
    
    /* Set hardware address */
    switch (cardtype) {
    case MBH10304:
    case TDK:
    case LA501:
    case CONTEC:
    case NEC:
    case KME:
	if (cardtype == MBH10304) {
	    card_name = "FMV-J182";

	    len = pcmcia_get_tuple(link, CISTPL_FUNCE, &buf);
	    if (len < 11) {
		    kfree(buf);
		    goto failed;
	    }
	    /* Read MACID from CIS */
	    for (i = 0; i < 6; i++)
		    dev->dev_addr[i] = buf[i + 5];
	    kfree(buf);
	} else {
	    if (pcmcia_get_mac_from_cis(link, dev))
		goto failed;
	    if( cardtype == TDK ) {
		card_name = "TDK LAK-CD021";
	    } else if( cardtype == LA501 ) {
		card_name = "LA501";
	    } else if( cardtype == NEC ) {
		card_name = "PK-UG-J001";
	    } else if( cardtype == KME ) {
		card_name = "Panasonic";
	    } else {
		card_name = "C-NET(PC)C";
	    }
	}
	break;
    case UNGERMANN:
	/* Read MACID from register */
	for (i = 0; i < 6; i++) 
	    dev->dev_addr[i] = inb(ioaddr + UNGERMANN_MAC_ID + i);
	card_name = "Access/CARD";
	break;
    case XXX10304:
	/* Read MACID from Buggy CIS */
	if (fmvj18x_get_hwinfo(link, buggybuf) == -1) {
	    pr_notice("unable to read hardware net address\n");
	    goto failed;
	}
	for (i = 0 ; i < 6; i++) {
	    dev->dev_addr[i] = buggybuf[i];
	}
	card_name = "FMV-J182";
	break;
    case MBH10302:
    default:
	/* Read MACID from register */
	for (i = 0; i < 6; i++) 
	    dev->dev_addr[i] = inb(ioaddr + MAC_ID + i);
	card_name = "FMV-J181";
	break;
    }

    lp->cardtype = cardtype;
    SET_NETDEV_DEV(dev, &link->dev);

    if (register_netdev(dev) != 0) {
	pr_notice("register_netdev() failed\n");
	goto failed;
    }

    /* print current configuration */
    netdev_info(dev, "%s, sram %s, port %#3lx, irq %d, hw_addr %pM\n",
		card_name, sram_config == 0 ? "4K TX*2" : "8K TX*2",
		dev->base_addr, dev->irq, dev->dev_addr);

    return 0;
    
failed:
    fmvj18x_release(link);
    return -ENODEV;
}