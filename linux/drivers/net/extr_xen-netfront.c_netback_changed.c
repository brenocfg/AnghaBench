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
struct xenbus_device {int const state; int /*<<< orphan*/  dev; } ;
struct netfront_info {struct net_device* netdev; } ;
struct net_device {int dummy; } ;
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;

/* Variables and functions */
#define  XenbusStateClosed 136 
#define  XenbusStateClosing 135 
#define  XenbusStateConnected 134 
#define  XenbusStateInitWait 133 
#define  XenbusStateInitialised 132 
#define  XenbusStateInitialising 131 
#define  XenbusStateReconfigured 130 
#define  XenbusStateReconfiguring 129 
#define  XenbusStateUnknown 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct netfront_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_wq ; 
 int /*<<< orphan*/  netdev_notify_peers (struct net_device*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_frontend_closed (struct xenbus_device*) ; 
 int /*<<< orphan*/  xenbus_strstate (int) ; 
 int /*<<< orphan*/  xenbus_switch_state (struct xenbus_device*,int) ; 
 int /*<<< orphan*/  xennet_connect (struct net_device*) ; 

__attribute__((used)) static void netback_changed(struct xenbus_device *dev,
			    enum xenbus_state backend_state)
{
	struct netfront_info *np = dev_get_drvdata(&dev->dev);
	struct net_device *netdev = np->netdev;

	dev_dbg(&dev->dev, "%s\n", xenbus_strstate(backend_state));

	wake_up_all(&module_wq);

	switch (backend_state) {
	case XenbusStateInitialising:
	case XenbusStateInitialised:
	case XenbusStateReconfiguring:
	case XenbusStateReconfigured:
	case XenbusStateUnknown:
		break;

	case XenbusStateInitWait:
		if (dev->state != XenbusStateInitialising)
			break;
		if (xennet_connect(netdev) != 0)
			break;
		xenbus_switch_state(dev, XenbusStateConnected);
		break;

	case XenbusStateConnected:
		netdev_notify_peers(netdev);
		break;

	case XenbusStateClosed:
		if (dev->state == XenbusStateClosed)
			break;
		/* Fall through - Missed the backend's CLOSING state. */
	case XenbusStateClosing:
		xenbus_frontend_closed(dev);
		break;
	}
}