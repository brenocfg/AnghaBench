#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ u8 ;
struct pcmcia_device {scalar_t__ has_manf_id; int manf_id; int io_lines; int /*<<< orphan*/  dev; TYPE_1__** resource; scalar_t__ irq; int /*<<< orphan*/  config_flags; struct net_device* priv; } ;
struct net_device {int if_port; unsigned int base_addr; scalar_t__* dev_addr; scalar_t__ irq; } ;
struct local_info {char* manf_str; int probe_port; scalar_t__ dingo; scalar_t__ mohawk; int /*<<< orphan*/ * dingo_ccr; scalar_t__ modem; } ;
struct TYPE_3__ {int end; int flags; unsigned int start; } ;

/* Variables and functions */
 int CISREG_COR ; 
 int CISREG_IOBASE_0 ; 
 int CISREG_IOBASE_1 ; 
 int /*<<< orphan*/  CISTPL_FUNCE ; 
 scalar_t__ CISTPL_FUNCE_LAN_NODE_ID ; 
 int /*<<< orphan*/  CONF_AUTO_SET_IO ; 
 int /*<<< orphan*/  CONF_ENABLE_IRQ ; 
 int /*<<< orphan*/  CONF_ENABLE_SPKR ; 
 int ENODEV ; 
 int IO_DATA_PATH_WIDTH_16 ; 
#define  MANFID_ACCTON 133 
#define  MANFID_COMPAQ 132 
#define  MANFID_COMPAQ2 131 
#define  MANFID_INTEL 130 
#define  MANFID_TOSHIBA 129 
#define  MANFID_XIRCOM 128 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int WIN_DATA_WIDTH_8 ; 
 int WIN_ENABLE ; 
 int WIN_MEMORY_TYPE_AM ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  do_reset (struct net_device*,int) ; 
 scalar_t__ do_sound ; 
 int i ; 
 int if_port ; 
 int /*<<< orphan*/ * ioremap (int,int) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,char*,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 struct local_info* netdev_priv (struct net_device*) ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 int /*<<< orphan*/  pcmcia_get_mac_ce ; 
 int pcmcia_get_mac_from_cis (struct pcmcia_device*,struct net_device*) ; 
 size_t pcmcia_get_tuple (struct pcmcia_device*,int,scalar_t__**) ; 
 int /*<<< orphan*/  pcmcia_loop_config (struct pcmcia_device*,int /*<<< orphan*/ ,int*) ; 
 int pcmcia_loop_tuple (struct pcmcia_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int pcmcia_map_mem_page (struct pcmcia_device*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int pcmcia_request_io (struct pcmcia_device*) ; 
 int pcmcia_request_irq (struct pcmcia_device*,int /*<<< orphan*/ ) ; 
 int pcmcia_request_window (struct pcmcia_device*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int pcmcia_write_config_byte (struct pcmcia_device*,int,int) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_notice (char*,...) ; 
 int /*<<< orphan*/  readb (int /*<<< orphan*/ *) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  set_card_type (struct pcmcia_device*) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xirc2ps_config_check ; 
 int /*<<< orphan*/  xirc2ps_config_modem ; 
 int /*<<< orphan*/  xirc2ps_interrupt ; 
 int /*<<< orphan*/  xirc2ps_release (struct pcmcia_device*) ; 

__attribute__((used)) static int
xirc2ps_config(struct pcmcia_device * link)
{
    struct net_device *dev = link->priv;
    struct local_info *local = netdev_priv(dev);
    unsigned int ioaddr;
    int err;
    u8 *buf;
    size_t len;

    local->dingo_ccr = NULL;

    dev_dbg(&link->dev, "config\n");

    /* Is this a valid	card */
    if (link->has_manf_id == 0) {
	pr_notice("manfid not found in CIS\n");
	goto failure;
    }

    switch (link->manf_id) {
      case MANFID_XIRCOM:
	local->manf_str = "Xircom";
	break;
      case MANFID_ACCTON:
	local->manf_str = "Accton";
	break;
      case MANFID_COMPAQ:
      case MANFID_COMPAQ2:
	local->manf_str = "Compaq";
	break;
      case MANFID_INTEL:
	local->manf_str = "Intel";
	break;
      case MANFID_TOSHIBA:
	local->manf_str = "Toshiba";
	break;
      default:
	pr_notice("Unknown Card Manufacturer ID: 0x%04x\n",
		  (unsigned)link->manf_id);
	goto failure;
    }
    dev_dbg(&link->dev, "found %s card\n", local->manf_str);

    if (!set_card_type(link)) {
	pr_notice("this card is not supported\n");
	goto failure;
    }

    /* get the ethernet address from the CIS */
    err = pcmcia_get_mac_from_cis(link, dev);

    /* not found: try to get the node-id from tuple 0x89 */
    if (err) {
	    len = pcmcia_get_tuple(link, 0x89, &buf);
	    /* data layout looks like tuple 0x22 */
	    if (buf && len == 8) {
		    if (*buf == CISTPL_FUNCE_LAN_NODE_ID) {
			    int i;
			    for (i = 2; i < 6; i++)
				    dev->dev_addr[i] = buf[i+2];
		    } else
			    err = -1;
	    }
	    kfree(buf);
    }

    if (err)
	err = pcmcia_loop_tuple(link, CISTPL_FUNCE, pcmcia_get_mac_ce, dev);

    if (err) {
	pr_notice("node-id not found in CIS\n");
	goto failure;
    }

    if (local->modem) {
	int pass;
	link->config_flags |= CONF_AUTO_SET_IO;

	if (local->dingo) {
	    /* Take the Modem IO port from the CIS and scan for a free
	     * Ethernet port */
	    if (!pcmcia_loop_config(link, xirc2ps_config_modem, NULL))
		    goto port_found;
	} else {
	    /* We do 2 passes here: The first one uses the regular mapping and
	     * the second tries again, thereby considering that the 32 ports are
	     * mirrored every 32 bytes. Actually we use a mirrored port for
	     * the Mako if (on the first pass) the COR bit 5 is set.
	     */
	    for (pass=0; pass < 2; pass++)
		    if (!pcmcia_loop_config(link, xirc2ps_config_check,
						    &pass))
			    goto port_found;
	    /* if special option:
	     * try to configure as Ethernet only.
	     * .... */
	}
	pr_notice("no ports available\n");
    } else {
	link->io_lines = 10;
	link->resource[0]->end = 16;
	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_16;
	for (ioaddr = 0x300; ioaddr < 0x400; ioaddr += 0x10) {
	    link->resource[0]->start = ioaddr;
	    if (!(err = pcmcia_request_io(link)))
		goto port_found;
	}
	link->resource[0]->start = 0; /* let CS decide */
	if ((err = pcmcia_request_io(link)))
	    goto config_error;
    }
  port_found:
    if (err)
	 goto config_error;

    /****************
     * Now allocate an interrupt line.	Note that this does not
     * actually assign a handler to the interrupt.
     */
    if ((err=pcmcia_request_irq(link, xirc2ps_interrupt)))
	goto config_error;

    link->config_flags |= CONF_ENABLE_IRQ;
    if (do_sound)
	    link->config_flags |= CONF_ENABLE_SPKR;

    if ((err = pcmcia_enable_device(link)))
	goto config_error;

    if (local->dingo) {
	/* Reset the modem's BAR to the correct value
	 * This is necessary because in the RequestConfiguration call,
	 * the base address of the ethernet port (BasePort1) is written
	 * to the BAR registers of the modem.
	 */
	err = pcmcia_write_config_byte(link, CISREG_IOBASE_0, (u8)
				link->resource[1]->start & 0xff);
	if (err)
	    goto config_error;

	err = pcmcia_write_config_byte(link, CISREG_IOBASE_1,
				(link->resource[1]->start >> 8) & 0xff);
	if (err)
	    goto config_error;

	/* There is no config entry for the Ethernet part which
	 * is at 0x0800. So we allocate a window into the attribute
	 * memory and write direct to the CIS registers
	 */
	link->resource[2]->flags = WIN_DATA_WIDTH_8 | WIN_MEMORY_TYPE_AM |
					WIN_ENABLE;
	link->resource[2]->start = link->resource[2]->end = 0;
	if ((err = pcmcia_request_window(link, link->resource[2], 0)))
	    goto config_error;

	local->dingo_ccr = ioremap(link->resource[2]->start, 0x1000) + 0x0800;
	if ((err = pcmcia_map_mem_page(link, link->resource[2], 0)))
	    goto config_error;

	/* Setup the CCRs; there are no infos in the CIS about the Ethernet
	 * part.
	 */
	writeb(0x47, local->dingo_ccr + CISREG_COR);
	ioaddr = link->resource[0]->start;
	writeb(ioaddr & 0xff	  , local->dingo_ccr + CISREG_IOBASE_0);
	writeb((ioaddr >> 8)&0xff , local->dingo_ccr + CISREG_IOBASE_1);

      #if 0
	{
	    u_char tmp;
	    pr_info("ECOR:");
	    for (i=0; i < 7; i++) {
		tmp = readb(local->dingo_ccr + i*2);
		pr_cont(" %02x", tmp);
	    }
	    pr_cont("\n");
	    pr_info("DCOR:");
	    for (i=0; i < 4; i++) {
		tmp = readb(local->dingo_ccr + 0x20 + i*2);
		pr_cont(" %02x", tmp);
	    }
	    pr_cont("\n");
	    pr_info("SCOR:");
	    for (i=0; i < 10; i++) {
		tmp = readb(local->dingo_ccr + 0x40 + i*2);
		pr_cont(" %02x", tmp);
	    }
	    pr_cont("\n");
	}
      #endif

	writeb(0x01, local->dingo_ccr + 0x20);
	writeb(0x0c, local->dingo_ccr + 0x22);
	writeb(0x00, local->dingo_ccr + 0x24);
	writeb(0x00, local->dingo_ccr + 0x26);
	writeb(0x00, local->dingo_ccr + 0x28);
    }

    /* The if_port symbol can be set when the module is loaded */
    local->probe_port=0;
    if (!if_port) {
	local->probe_port = dev->if_port = 1;
    } else if ((if_port >= 1 && if_port <= 2) ||
	       (local->mohawk && if_port==4))
	dev->if_port = if_port;
    else
	pr_notice("invalid if_port requested\n");

    /* we can now register the device with the net subsystem */
    dev->irq = link->irq;
    dev->base_addr = link->resource[0]->start;

    if (local->dingo)
	do_reset(dev, 1); /* a kludge to make the cem56 work */

    SET_NETDEV_DEV(dev, &link->dev);

    if ((err=register_netdev(dev))) {
	pr_notice("register_netdev() failed\n");
	goto config_error;
    }

    /* give some infos about the hardware */
    netdev_info(dev, "%s: port %#3lx, irq %d, hwaddr %pM\n",
		local->manf_str, (u_long)dev->base_addr, (int)dev->irq,
		dev->dev_addr);

    return 0;

  config_error:
    xirc2ps_release(link);
    return -ENODEV;

  failure:
    return -ENODEV;
}