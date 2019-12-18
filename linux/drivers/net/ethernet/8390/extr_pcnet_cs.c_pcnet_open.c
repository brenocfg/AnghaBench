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
struct pcnet_dev {int link_status; int /*<<< orphan*/  watchdog; int /*<<< orphan*/  eth_phy; int /*<<< orphan*/  phy_id; struct pcmcia_device* p_dev; } ;
struct pcmcia_device {int /*<<< orphan*/  open; int /*<<< orphan*/  dev; } ;
struct net_device {unsigned int base_addr; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ EN0_ISR ; 
 int ENODEV ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 struct pcnet_dev* PRIV (struct net_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ei_irq_wrapper ; 
 int ei_open (struct net_device*) ; 
 int /*<<< orphan*/  ei_watchdog ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 int /*<<< orphan*/  pcmcia_dev_present (struct pcmcia_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  set_misc_reg (struct net_device*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcnet_open(struct net_device *dev)
{
    int ret;
    struct pcnet_dev *info = PRIV(dev);
    struct pcmcia_device *link = info->p_dev;
    unsigned int nic_base = dev->base_addr;

    dev_dbg(&link->dev, "pcnet_open('%s')\n", dev->name);

    if (!pcmcia_dev_present(link))
	return -ENODEV;

    set_misc_reg(dev);

    outb_p(0xFF, nic_base + EN0_ISR); /* Clear bogus intr. */
    ret = request_irq(dev->irq, ei_irq_wrapper, IRQF_SHARED, dev->name, dev);
    if (ret)
	    return ret;

    link->open++;

    info->phy_id = info->eth_phy;
    info->link_status = 0x00;
    timer_setup(&info->watchdog, ei_watchdog, 0);
    mod_timer(&info->watchdog, jiffies + HZ);

    return ei_open(dev);
}