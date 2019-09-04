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
struct pcmcia_device {int /*<<< orphan*/  open; int /*<<< orphan*/  dev; } ;
struct net_device {unsigned int base_addr; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct axnet_dev {int link_status; int /*<<< orphan*/  watchdog; struct pcmcia_device* p_dev; } ;

/* Variables and functions */
 scalar_t__ EN0_ISR ; 
 int ENODEV ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 struct axnet_dev* PRIV (struct net_device*) ; 
 int ax_open (struct net_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ei_irq_wrapper ; 
 int /*<<< orphan*/  ei_watchdog ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 int /*<<< orphan*/  pcmcia_dev_present (struct pcmcia_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct net_device*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axnet_open(struct net_device *dev)
{
    int ret;
    struct axnet_dev *info = PRIV(dev);
    struct pcmcia_device *link = info->p_dev;
    unsigned int nic_base = dev->base_addr;
    
    dev_dbg(&link->dev, "axnet_open('%s')\n", dev->name);

    if (!pcmcia_dev_present(link))
	return -ENODEV;

    outb_p(0xFF, nic_base + EN0_ISR); /* Clear bogus intr. */
    ret = request_irq(dev->irq, ei_irq_wrapper, IRQF_SHARED, "axnet_cs", dev);
    if (ret)
	    return ret;

    link->open++;

    info->link_status = 0x00;
    timer_setup(&info->watchdog, ei_watchdog, 0);
    mod_timer(&info->watchdog, jiffies + HZ);

    return ax_open(dev);
}