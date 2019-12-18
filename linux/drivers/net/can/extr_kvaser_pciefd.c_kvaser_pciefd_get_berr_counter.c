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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  txerr; int /*<<< orphan*/  rxerr; } ;
struct kvaser_pciefd_can {TYPE_1__ bec; } ;
struct can_berr_counter {int /*<<< orphan*/  txerr; int /*<<< orphan*/  rxerr; } ;

/* Variables and functions */
 struct kvaser_pciefd_can* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static int kvaser_pciefd_get_berr_counter(const struct net_device *ndev,
					  struct can_berr_counter *bec)
{
	struct kvaser_pciefd_can *can = netdev_priv(ndev);

	bec->rxerr = can->bec.rxerr;
	bec->txerr = can->bec.txerr;
	return 0;
}