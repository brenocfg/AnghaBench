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
struct usbnet {TYPE_1__* driver_info; int /*<<< orphan*/  bh; int /*<<< orphan*/  txq; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* recover ) (struct usbnet*) ;} ;

/* Variables and functions */
 struct usbnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct usbnet*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink_urbs (struct usbnet*,int /*<<< orphan*/ *) ; 

void usbnet_tx_timeout (struct net_device *net)
{
	struct usbnet		*dev = netdev_priv(net);

	unlink_urbs (dev, &dev->txq);
	tasklet_schedule (&dev->bh);
	/* this needs to be handled individually because the generic layer
	 * doesn't know what is sufficient and could not restore private
	 * information if a remedy of an unconditional reset were used.
	 */
	if (dev->driver_info->recover)
		(dev->driver_info->recover)(dev);
}