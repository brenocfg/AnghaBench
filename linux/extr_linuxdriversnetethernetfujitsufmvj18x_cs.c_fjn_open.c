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
struct pcmcia_device {int /*<<< orphan*/  open; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct local_info {int /*<<< orphan*/  open_time; scalar_t__ tx_queue_len; scalar_t__ tx_queue; scalar_t__ tx_started; struct pcmcia_device* p_dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  fjn_reset (struct net_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct local_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  pcmcia_dev_present (struct pcmcia_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fjn_open(struct net_device *dev)
{
    struct local_info *lp = netdev_priv(dev);
    struct pcmcia_device *link = lp->p_dev;

    pr_debug("fjn_open('%s').\n", dev->name);

    if (!pcmcia_dev_present(link))
	return -ENODEV;
    
    link->open++;
    
    fjn_reset(dev);
    
    lp->tx_started = 0;
    lp->tx_queue = 0;
    lp->tx_queue_len = 0;
    lp->open_time = jiffies;
    netif_start_queue(dev);
    
    return 0;
}