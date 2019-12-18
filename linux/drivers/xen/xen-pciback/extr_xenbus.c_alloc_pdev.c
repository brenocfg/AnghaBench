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
struct xen_pcibk_device {int /*<<< orphan*/  op_work; scalar_t__ be_watching; int /*<<< orphan*/  evtchn_irq; int /*<<< orphan*/ * sh_info; int /*<<< orphan*/  dev_lock; struct xenbus_device* xdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVALID_EVTCHN_IRQ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct xen_pcibk_device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct xen_pcibk_device*) ; 
 int /*<<< orphan*/  kfree (struct xen_pcibk_device*) ; 
 struct xen_pcibk_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_pcibk_do_op ; 
 scalar_t__ xen_pcibk_init_devices (struct xen_pcibk_device*) ; 

__attribute__((used)) static struct xen_pcibk_device *alloc_pdev(struct xenbus_device *xdev)
{
	struct xen_pcibk_device *pdev;

	pdev = kzalloc(sizeof(struct xen_pcibk_device), GFP_KERNEL);
	if (pdev == NULL)
		goto out;
	dev_dbg(&xdev->dev, "allocated pdev @ 0x%p\n", pdev);

	pdev->xdev = xdev;

	mutex_init(&pdev->dev_lock);

	pdev->sh_info = NULL;
	pdev->evtchn_irq = INVALID_EVTCHN_IRQ;
	pdev->be_watching = 0;

	INIT_WORK(&pdev->op_work, xen_pcibk_do_op);

	if (xen_pcibk_init_devices(pdev)) {
		kfree(pdev);
		pdev = NULL;
	}

	dev_set_drvdata(&xdev->dev, pdev);

out:
	return pdev;
}