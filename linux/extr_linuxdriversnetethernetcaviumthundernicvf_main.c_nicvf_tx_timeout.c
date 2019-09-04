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
struct nicvf {int /*<<< orphan*/  reset_task; TYPE_1__* drv_stats; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_timeout; } ;

/* Variables and functions */
 struct nicvf* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_warn (struct nicvf*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_err ; 

__attribute__((used)) static void nicvf_tx_timeout(struct net_device *dev)
{
	struct nicvf *nic = netdev_priv(dev);

	netif_warn(nic, tx_err, dev, "Transmit timed out, resetting\n");

	this_cpu_inc(nic->drv_stats->tx_timeout);
	schedule_work(&nic->reset_task);
}