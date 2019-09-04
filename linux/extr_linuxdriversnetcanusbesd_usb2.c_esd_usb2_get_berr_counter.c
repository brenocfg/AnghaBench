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
struct TYPE_2__ {int /*<<< orphan*/  rxerr; int /*<<< orphan*/  txerr; } ;
struct esd_usb2_net_priv {TYPE_1__ bec; } ;
struct can_berr_counter {int /*<<< orphan*/  rxerr; int /*<<< orphan*/  txerr; } ;

/* Variables and functions */
 struct esd_usb2_net_priv* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static int esd_usb2_get_berr_counter(const struct net_device *netdev,
				     struct can_berr_counter *bec)
{
	struct esd_usb2_net_priv *priv = netdev_priv(netdev);

	bec->txerr = priv->bec.txerr;
	bec->rxerr = priv->bec.rxerr;

	return 0;
}