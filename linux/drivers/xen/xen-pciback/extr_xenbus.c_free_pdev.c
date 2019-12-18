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
struct xen_pcibk_device {TYPE_1__* xdev; scalar_t__ be_watching; int /*<<< orphan*/  be_watch; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct xen_pcibk_device*) ; 
 int /*<<< orphan*/  unregister_xenbus_watch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_pcibk_disconnect (struct xen_pcibk_device*) ; 
 int /*<<< orphan*/  xen_pcibk_release_devices (struct xen_pcibk_device*) ; 

__attribute__((used)) static void free_pdev(struct xen_pcibk_device *pdev)
{
	if (pdev->be_watching) {
		unregister_xenbus_watch(&pdev->be_watch);
		pdev->be_watching = 0;
	}

	xen_pcibk_disconnect(pdev);

	/* N.B. This calls pcistub_put_pci_dev which does the FLR on all
	 * of the PCIe devices. */
	xen_pcibk_release_devices(pdev);

	dev_set_drvdata(&pdev->xdev->dev, NULL);
	pdev->xdev = NULL;

	kfree(pdev);
}