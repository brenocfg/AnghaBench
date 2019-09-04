#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  netdev; int /*<<< orphan*/  isdn_channel; int /*<<< orphan*/  isdn_device; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ isdn_net_local ;
struct TYPE_5__ {int /*<<< orphan*/ * st_netdev; int /*<<< orphan*/ * rx_netdev; int /*<<< orphan*/ * chanmap; int /*<<< orphan*/ * drvmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISDN_NET_CONNECTED ; 
 TYPE_3__* dev ; 

__attribute__((used)) static void
isdn_net_bind_channel(isdn_net_local *lp, int idx)
{
	lp->flags |= ISDN_NET_CONNECTED;
	lp->isdn_device = dev->drvmap[idx];
	lp->isdn_channel = dev->chanmap[idx];
	dev->rx_netdev[idx] = lp->netdev;
	dev->st_netdev[idx] = lp->netdev;
}