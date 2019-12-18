#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {TYPE_1__** resource; struct net_device* priv; } ;
struct net_device {unsigned int base_addr; } ;
struct local_info {int /*<<< orphan*/ * base; } ;
struct TYPE_4__ {int flags; scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int WIN_DATA_WIDTH_8 ; 
 int WIN_ENABLE ; 
 int WIN_MEMORY_TYPE_AM ; 
 int /*<<< orphan*/ * ioremap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*) ; 
 struct local_info* netdev_priv (struct net_device*) ; 
 int pcmcia_map_mem_page (struct pcmcia_device*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int pcmcia_request_window (struct pcmcia_device*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fmvj18x_setup_mfc(struct pcmcia_device *link)
{
    int i;
    struct net_device *dev = link->priv;
    unsigned int ioaddr;
    struct local_info *lp = netdev_priv(dev);

    /* Allocate a small memory window */
    link->resource[3]->flags = WIN_DATA_WIDTH_8|WIN_MEMORY_TYPE_AM|WIN_ENABLE;
    link->resource[3]->start = link->resource[3]->end = 0;
    i = pcmcia_request_window(link, link->resource[3], 0);
    if (i != 0)
	return -1;

    lp->base = ioremap(link->resource[3]->start,
		       resource_size(link->resource[3]));
    if (lp->base == NULL) {
	netdev_notice(dev, "ioremap failed\n");
	return -1;
    }

    i = pcmcia_map_mem_page(link, link->resource[3], 0);
    if (i != 0) {
	iounmap(lp->base);
	lp->base = NULL;
	return -1;
    }
    
    ioaddr = dev->base_addr;
    writeb(0x47, lp->base+0x800);	/* Config Option Register of LAN */
    writeb(0x0,  lp->base+0x802);	/* Config and Status Register */

    writeb(ioaddr & 0xff, lp->base+0x80a);	  /* I/O Base(Low) of LAN */
    writeb((ioaddr >> 8) & 0xff, lp->base+0x80c); /* I/O Base(High) of LAN */
   
    writeb(0x45, lp->base+0x820);	/* Config Option Register of Modem */
    writeb(0x8,  lp->base+0x822);	/* Config and Status Register */

    return 0;

}