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
struct ocxl_fn_config {int max_pasid_log; scalar_t__ max_afu_index; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OCXL_MAX_AFU_PER_FUNCTION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int validate_function(struct pci_dev *dev, struct ocxl_fn_config *fn)
{
	if (fn->max_pasid_log == -1 && fn->max_afu_index >= 0) {
		dev_err(&dev->dev,
			"AFUs are defined but no PASIDs are requested\n");
		return -EINVAL;
	}

	if (fn->max_afu_index > OCXL_MAX_AFU_PER_FUNCTION) {
		dev_err(&dev->dev,
			"Max AFU index out of architectural limit (%d vs %d)\n",
			fn->max_afu_index, OCXL_MAX_AFU_PER_FUNCTION);
		return -EINVAL;
	}
	return 0;
}