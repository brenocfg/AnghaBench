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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ocxl_fn_config {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int read_dvsec_afu_info (struct pci_dev*,struct ocxl_fn_config*) ; 
 int read_dvsec_function (struct pci_dev*,struct ocxl_fn_config*) ; 
 int read_dvsec_tl (struct pci_dev*,struct ocxl_fn_config*) ; 
 int read_dvsec_vendor (struct pci_dev*) ; 
 int /*<<< orphan*/  read_pasid (struct pci_dev*,struct ocxl_fn_config*) ; 
 int validate_function (struct pci_dev*,struct ocxl_fn_config*) ; 

int ocxl_config_read_function(struct pci_dev *dev, struct ocxl_fn_config *fn)
{
	int rc;

	read_pasid(dev, fn);

	rc = read_dvsec_tl(dev, fn);
	if (rc) {
		dev_err(&dev->dev,
			"Invalid Transaction Layer DVSEC configuration: %d\n",
			rc);
		return -ENODEV;
	}

	rc = read_dvsec_function(dev, fn);
	if (rc) {
		dev_err(&dev->dev,
			"Invalid Function DVSEC configuration: %d\n", rc);
		return -ENODEV;
	}

	rc = read_dvsec_afu_info(dev, fn);
	if (rc) {
		dev_err(&dev->dev, "Invalid AFU configuration: %d\n", rc);
		return -ENODEV;
	}

	rc = read_dvsec_vendor(dev);
	if (rc) {
		dev_err(&dev->dev,
			"Invalid vendor specific DVSEC configuration: %d\n",
			rc);
		return -ENODEV;
	}

	rc = validate_function(dev, fn);
	return rc;
}