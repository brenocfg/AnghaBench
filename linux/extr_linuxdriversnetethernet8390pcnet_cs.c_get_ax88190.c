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
struct pcmcia_device {int config_base; struct net_device* priv; } ;
struct net_device {unsigned int base_addr; int* dev_addr; } ;
struct hw_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ E8390_CMD ; 
 int E8390_RREAD ; 
 int E8390_START ; 
 scalar_t__ EN0_DCFG ; 
 scalar_t__ EN0_RSARHI ; 
 scalar_t__ EN0_RSARLO ; 
 scalar_t__ PCNET_DATAPORT ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 

__attribute__((used)) static struct hw_info *get_ax88190(struct pcmcia_device *link)
{
    struct net_device *dev = link->priv;
    unsigned int ioaddr = dev->base_addr;
    int i, j;

    /* Not much of a test, but the alternatives are messy */
    if (link->config_base != 0x03c0)
	return NULL;

    outb_p(0x01, ioaddr + EN0_DCFG);	/* Set word-wide access. */
    outb_p(0x00, ioaddr + EN0_RSARLO);	/* DMA starting at 0x0400. */
    outb_p(0x04, ioaddr + EN0_RSARHI);
    outb_p(E8390_RREAD+E8390_START, ioaddr + E8390_CMD);

    for (i = 0; i < 6; i += 2) {
	j = inw(ioaddr + PCNET_DATAPORT);
	dev->dev_addr[i] = j & 0xff;
	dev->dev_addr[i+1] = j >> 8;
    }
    return NULL;
}