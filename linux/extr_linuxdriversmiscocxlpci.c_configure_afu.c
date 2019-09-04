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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ocxl_afu {int /*<<< orphan*/  config; TYPE_1__* fn; } ;
struct TYPE_2__ {int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int assign_afu_actag (struct ocxl_afu*,struct pci_dev*) ; 
 int assign_afu_pasid (struct ocxl_afu*,struct pci_dev*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int map_mmio_areas (struct ocxl_afu*,struct pci_dev*) ; 
 int ocxl_config_read_afu (struct pci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reclaim_afu_actag (struct ocxl_afu*) ; 
 int /*<<< orphan*/  reclaim_afu_pasid (struct ocxl_afu*) ; 
 int set_afu_device (struct ocxl_afu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int configure_afu(struct ocxl_afu *afu, u8 afu_idx, struct pci_dev *dev)
{
	int rc;

	rc = ocxl_config_read_afu(dev, &afu->fn->config, &afu->config, afu_idx);
	if (rc)
		return rc;

	rc = set_afu_device(afu, dev_name(&dev->dev));
	if (rc)
		return rc;

	rc = assign_afu_actag(afu, dev);
	if (rc)
		return rc;

	rc = assign_afu_pasid(afu, dev);
	if (rc) {
		reclaim_afu_actag(afu);
		return rc;
	}

	rc = map_mmio_areas(afu, dev);
	if (rc) {
		reclaim_afu_pasid(afu);
		reclaim_afu_actag(afu);
		return rc;
	}
	return 0;
}