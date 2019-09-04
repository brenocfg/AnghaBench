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
struct ocxl_afu_config {int global_mmio_bar; int pp_mmio_bar; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int EINVAL ; 
 int OCXL_TEMPL_NAME_LEN ; 
 int /*<<< orphan*/  char_allowed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int validate_afu(struct pci_dev *dev, struct ocxl_afu_config *afu)
{
	int i;

	if (!afu->name[0]) {
		dev_err(&dev->dev, "Empty AFU name\n");
		return -EINVAL;
	}
	for (i = 0; i < OCXL_TEMPL_NAME_LEN; i++) {
		if (!char_allowed(afu->name[i])) {
			dev_err(&dev->dev,
				"Invalid character in AFU name\n");
			return -EINVAL;
		}
	}

	if (afu->global_mmio_bar != 0 &&
		afu->global_mmio_bar != 2 &&
		afu->global_mmio_bar != 4) {
		dev_err(&dev->dev, "Invalid global MMIO bar number\n");
		return -EINVAL;
	}
	if (afu->pp_mmio_bar != 0 &&
		afu->pp_mmio_bar != 2 &&
		afu->pp_mmio_bar != 4) {
		dev_err(&dev->dev, "Invalid per-process MMIO bar number\n");
		return -EINVAL;
	}
	return 0;
}