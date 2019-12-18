#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  max_timeout; int /*<<< orphan*/  min_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct esb_dev {struct pci_dev* pdev; int /*<<< orphan*/  base; TYPE_1__ wdd; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ESB_HEARTBEAT_DEFAULT ; 
 int /*<<< orphan*/  ESB_HEARTBEAT_MAX ; 
 int /*<<< orphan*/  ESB_HEARTBEAT_MIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct esb_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esb_getdevice (struct esb_dev*) ; 
 int /*<<< orphan*/  esb_info ; 
 int /*<<< orphan*/  esb_initdevice (struct esb_dev*) ; 
 int /*<<< orphan*/  esb_ops ; 
 int /*<<< orphan*/  heartbeat ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_stop_on_unregister (TYPE_1__*) ; 

__attribute__((used)) static int esb_probe(struct pci_dev *pdev,
		const struct pci_device_id *ent)
{
	struct esb_dev *edev;
	int ret;

	edev = devm_kzalloc(&pdev->dev, sizeof(*edev), GFP_KERNEL);
	if (!edev)
		return -ENOMEM;

	/* Check whether or not the hardware watchdog is there */
	edev->pdev = pdev;
	if (!esb_getdevice(edev))
		return -ENODEV;

	/* Initialize the watchdog and make sure it does not run */
	edev->wdd.info = &esb_info;
	edev->wdd.ops = &esb_ops;
	edev->wdd.min_timeout = ESB_HEARTBEAT_MIN;
	edev->wdd.max_timeout = ESB_HEARTBEAT_MAX;
	edev->wdd.timeout = ESB_HEARTBEAT_DEFAULT;
	watchdog_init_timeout(&edev->wdd, heartbeat, NULL);
	watchdog_set_nowayout(&edev->wdd, nowayout);
	watchdog_stop_on_reboot(&edev->wdd);
	watchdog_stop_on_unregister(&edev->wdd);
	esb_initdevice(edev);

	/* Register the watchdog so that userspace has access to it */
	ret = watchdog_register_device(&edev->wdd);
	if (ret != 0)
		goto err_unmap;
	dev_info(&pdev->dev,
		"initialized. heartbeat=%d sec (nowayout=%d)\n",
		edev->wdd.timeout, nowayout);
	return 0;

err_unmap:
	iounmap(edev->base);
	pci_release_region(edev->pdev, 0);
	pci_disable_device(edev->pdev);
	return ret;
}