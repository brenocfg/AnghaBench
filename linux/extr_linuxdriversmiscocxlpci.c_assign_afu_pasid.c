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
struct pci_dev {int dummy; } ;
struct ocxl_fn {scalar_t__ pasid_base; } ;
struct TYPE_2__ {int pasid_supported_log; int /*<<< orphan*/  dvsec_afu_control_pos; } ;
struct ocxl_afu {int pasid_max; scalar_t__ pasid_base; int /*<<< orphan*/  dev; TYPE_1__ config; int /*<<< orphan*/  pasid_count; struct ocxl_fn* fn; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  ocxl_config_set_afu_pasid (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int ocxl_pasid_afu_alloc (struct ocxl_fn*,int) ; 

__attribute__((used)) static int assign_afu_pasid(struct ocxl_afu *afu, struct pci_dev *dev)
{
	struct ocxl_fn *fn = afu->fn;
	int pasid_count, pasid_offset;

	/*
	 * We only support the case where the function configuration
	 * requested enough PASIDs to cover all AFUs.
	 */
	pasid_count = 1 << afu->config.pasid_supported_log;
	pasid_offset = ocxl_pasid_afu_alloc(fn, pasid_count);
	if (pasid_offset < 0) {
		dev_err(&afu->dev, "Can't allocate %d PASIDs for AFU: %d\n",
			pasid_count, pasid_offset);
		return pasid_offset;
	}
	afu->pasid_base = fn->pasid_base + pasid_offset;
	afu->pasid_count = 0;
	afu->pasid_max = pasid_count;

	ocxl_config_set_afu_pasid(dev, afu->config.dvsec_afu_control_pos,
				afu->pasid_base,
				afu->config.pasid_supported_log);
	dev_dbg(&afu->dev, "PASID base=%d, enabled=%d\n",
		afu->pasid_base, pasid_count);
	return 0;
}