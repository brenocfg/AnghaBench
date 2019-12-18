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
typedef  int /*<<< orphan*/  u8 ;
struct pcmcia_device {int io_lines; int /*<<< orphan*/  dev; TYPE_1__** resource; int /*<<< orphan*/  irq; struct net_device* priv; } ;
struct net_device {unsigned int base_addr; int if_port; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  irq; } ;
typedef  int /*<<< orphan*/  mace_private ;
struct TYPE_2__ {unsigned int start; } ;

/* Variables and functions */
 int ENODEV ; 
 size_t ETH_ALEN ; 
 int /*<<< orphan*/  MACE_CHIPIDH ; 
 int /*<<< orphan*/  MACE_CHIPIDL ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * if_names ; 
 int if_port ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int mace_init (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mace_interrupt ; 
 char mace_read (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nmclan_release (struct pcmcia_device*) ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 size_t pcmcia_get_tuple (struct pcmcia_device*,int,int /*<<< orphan*/ **) ; 
 int pcmcia_request_io (struct pcmcia_device*) ; 
 int pcmcia_request_irq (struct pcmcia_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,...) ; 
 int register_netdev (struct net_device*) ; 

__attribute__((used)) static int nmclan_config(struct pcmcia_device *link)
{
  struct net_device *dev = link->priv;
  mace_private *lp = netdev_priv(dev);
  u8 *buf;
  size_t len;
  int i, ret;
  unsigned int ioaddr;

  dev_dbg(&link->dev, "nmclan_config\n");

  link->io_lines = 5;
  ret = pcmcia_request_io(link);
  if (ret)
	  goto failed;
  ret = pcmcia_request_irq(link, mace_interrupt);
  if (ret)
	  goto failed;
  ret = pcmcia_enable_device(link);
  if (ret)
	  goto failed;

  dev->irq = link->irq;
  dev->base_addr = link->resource[0]->start;

  ioaddr = dev->base_addr;

  /* Read the ethernet address from the CIS. */
  len = pcmcia_get_tuple(link, 0x80, &buf);
  if (!buf || len < ETH_ALEN) {
	  kfree(buf);
	  goto failed;
  }
  memcpy(dev->dev_addr, buf, ETH_ALEN);
  kfree(buf);

  /* Verify configuration by reading the MACE ID. */
  {
    char sig[2];

    sig[0] = mace_read(lp, ioaddr, MACE_CHIPIDL);
    sig[1] = mace_read(lp, ioaddr, MACE_CHIPIDH);
    if ((sig[0] == 0x40) && ((sig[1] & 0x0F) == 0x09)) {
      dev_dbg(&link->dev, "nmclan_cs configured: mace id=%x %x\n",
	    sig[0], sig[1]);
    } else {
      pr_notice("mace id not found: %x %x should be 0x40 0x?9\n",
		sig[0], sig[1]);
      return -ENODEV;
    }
  }

  if(mace_init(lp, ioaddr, dev->dev_addr) == -1)
  	goto failed;

  /* The if_port symbol can be set when the module is loaded */
  if (if_port <= 2)
    dev->if_port = if_port;
  else
    pr_notice("invalid if_port requested\n");

  SET_NETDEV_DEV(dev, &link->dev);

  i = register_netdev(dev);
  if (i != 0) {
    pr_notice("register_netdev() failed\n");
    goto failed;
  }

  netdev_info(dev, "nmclan: port %#3lx, irq %d, %s port, hw_addr %pM\n",
	      dev->base_addr, dev->irq, if_names[dev->if_port], dev->dev_addr);
  return 0;

failed:
	nmclan_release(link);
	return -ENODEV;
}