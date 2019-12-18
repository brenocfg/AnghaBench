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
struct net_device {int dummy; } ;
struct de4x5_private {int (* infoleaf_fn ) (struct net_device*) ;} ;

/* Variables and functions */
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int stub1 (struct net_device*) ; 

__attribute__((used)) static int
srom_autoconf(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);

    return lp->infoleaf_fn(dev);
}