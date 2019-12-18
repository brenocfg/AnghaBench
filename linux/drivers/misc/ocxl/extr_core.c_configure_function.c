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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dvsec_tl_pos; } ;
struct ocxl_fn {int /*<<< orphan*/  link; TYPE_1__ config; } ;

/* Variables and functions */
 int assign_function_actag (struct ocxl_fn*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int ocxl_config_read_function (struct pci_dev*,TYPE_1__*) ; 
 int ocxl_config_set_TL (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocxl_link_release (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int ocxl_link_setup (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int set_function_device (struct ocxl_fn*,struct pci_dev*) ; 
 int set_function_pasid (struct ocxl_fn*) ; 

__attribute__((used)) static int configure_function(struct ocxl_fn *fn, struct pci_dev *dev)
{
	int rc;

	rc = pci_enable_device(dev);
	if (rc) {
		dev_err(&dev->dev, "pci_enable_device failed: %d\n", rc);
		return rc;
	}

	/*
	 * Once it has been confirmed to work on our hardware, we
	 * should reset the function, to force the adapter to restart
	 * from scratch.
	 * A function reset would also reset all its AFUs.
	 *
	 * Some hints for implementation:
	 *
	 * - there's not status bit to know when the reset is done. We
	 *   should try reading the config space to know when it's
	 *   done.
	 * - probably something like:
	 *	Reset
	 *	wait 100ms
	 *	issue config read
	 *	allow device up to 1 sec to return success on config
	 *	read before declaring it broken
	 *
	 * Some shared logic on the card (CFG, TLX) won't be reset, so
	 * there's no guarantee that it will be enough.
	 */
	rc = ocxl_config_read_function(dev, &fn->config);
	if (rc)
		return rc;

	rc = set_function_device(fn, dev);
	if (rc)
		return rc;

	rc = assign_function_actag(fn);
	if (rc)
		return rc;

	rc = set_function_pasid(fn);
	if (rc)
		return rc;

	rc = ocxl_link_setup(dev, 0, &fn->link);
	if (rc)
		return rc;

	rc = ocxl_config_set_TL(dev, fn->config.dvsec_tl_pos);
	if (rc) {
		ocxl_link_release(dev, fn->link);
		return rc;
	}
	return 0;
}