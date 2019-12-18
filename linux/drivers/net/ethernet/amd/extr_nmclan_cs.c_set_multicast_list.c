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
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int multicast_num_addrs; } ;
typedef  TYPE_1__ mace_private ;

/* Variables and functions */
 int netdev_mc_count (struct net_device*) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  restore_multicast_list (struct net_device*) ; 

__attribute__((used)) static void set_multicast_list(struct net_device *dev)
{
  mace_private *lp = netdev_priv(dev);

#ifdef PCMCIA_DEBUG
  {
    static int old;
    if (netdev_mc_count(dev) != old) {
      old = netdev_mc_count(dev);
      pr_debug("%s: setting Rx mode to %d addresses.\n",
	    dev->name, old);
    }
  }
#endif

  lp->multicast_num_addrs = netdev_mc_count(dev);
  restore_multicast_list(dev);

}