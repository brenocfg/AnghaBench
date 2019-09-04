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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int pnv_ocxl_get_actag (struct pci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ocxl_config_get_actag_info(struct pci_dev *dev, u16 *base, u16 *enabled,
			u16 *supported)
{
	int rc;

	/*
	 * This is really a simple wrapper for the kernel API, to
	 * avoid an external driver using ocxl as a library to call
	 * platform-dependent code
	 */
	rc = pnv_ocxl_get_actag(dev, base, enabled, supported);
	if (rc) {
		dev_err(&dev->dev, "Can't get actag for device: %d\n", rc);
		return rc;
	}
	return 0;
}