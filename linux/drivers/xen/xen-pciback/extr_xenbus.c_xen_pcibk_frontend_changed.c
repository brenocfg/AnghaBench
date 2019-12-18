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
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct xen_pcibk_device {int dummy; } ;
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;

/* Variables and functions */
#define  XenbusStateClosed 133 
#define  XenbusStateClosing 132 
#define  XenbusStateConnected 131 
#define  XenbusStateInitialised 130 
#define  XenbusStateReconfiguring 129 
#define  XenbusStateUnknown 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct xen_pcibk_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_pcibk_attach (struct xen_pcibk_device*) ; 
 int /*<<< orphan*/  xen_pcibk_disconnect (struct xen_pcibk_device*) ; 
 int /*<<< orphan*/  xen_pcibk_reconfigure (struct xen_pcibk_device*) ; 
 int /*<<< orphan*/  xenbus_dev_is_online (struct xenbus_device*) ; 
 int /*<<< orphan*/  xenbus_switch_state (struct xenbus_device*,int const) ; 

__attribute__((used)) static void xen_pcibk_frontend_changed(struct xenbus_device *xdev,
				     enum xenbus_state fe_state)
{
	struct xen_pcibk_device *pdev = dev_get_drvdata(&xdev->dev);

	dev_dbg(&xdev->dev, "fe state changed %d\n", fe_state);

	switch (fe_state) {
	case XenbusStateInitialised:
		xen_pcibk_attach(pdev);
		break;

	case XenbusStateReconfiguring:
		xen_pcibk_reconfigure(pdev);
		break;

	case XenbusStateConnected:
		/* pcifront switched its state from reconfiguring to connected.
		 * Then switch to connected state.
		 */
		xenbus_switch_state(xdev, XenbusStateConnected);
		break;

	case XenbusStateClosing:
		xen_pcibk_disconnect(pdev);
		xenbus_switch_state(xdev, XenbusStateClosing);
		break;

	case XenbusStateClosed:
		xen_pcibk_disconnect(pdev);
		xenbus_switch_state(xdev, XenbusStateClosed);
		if (xenbus_dev_is_online(xdev))
			break;
		/* fall through - if not online */
	case XenbusStateUnknown:
		dev_dbg(&xdev->dev, "frontend is gone! unregister device\n");
		device_unregister(&xdev->dev);
		break;

	default:
		break;
	}
}