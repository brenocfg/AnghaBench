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
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct axnet_dev {int /*<<< orphan*/  watchdog; struct pcmcia_device* p_dev; } ;

/* Variables and functions */
 struct axnet_dev* PRIV (struct net_device*) ; 
 int /*<<< orphan*/  ax_close (struct net_device*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int axnet_close(struct net_device *dev)
{
    struct axnet_dev *info = PRIV(dev);
    struct pcmcia_device *link = info->p_dev;

    dev_dbg(&link->dev, "axnet_close('%s')\n", dev->name);

    ax_close(dev);
    free_irq(dev->irq, dev);
    
    link->open--;
    netif_stop_queue(dev);
    del_timer_sync(&info->watchdog);

    return 0;
}