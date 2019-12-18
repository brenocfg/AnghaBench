#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct ocxl_fn {scalar_t__ pasid_base; TYPE_1__ dev; } ;
struct TYPE_4__ {int pasid_supported_log; int /*<<< orphan*/  dvsec_afu_control_pos; } ;
struct ocxl_afu {int pasid_max; scalar_t__ pasid_base; TYPE_2__ config; int /*<<< orphan*/  pasid_count; struct ocxl_fn* fn; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  ocxl_config_set_afu_pasid (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int ocxl_pasid_afu_alloc (struct ocxl_fn*,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int assign_afu_pasid(struct ocxl_afu *afu)
{
	struct ocxl_fn *fn = afu->fn;
	int pasid_count, pasid_offset;
	struct pci_dev *pci_dev = to_pci_dev(fn->dev.parent);

	/*
	 * We only support the case where the function configuration
	 * requested enough PASIDs to cover all AFUs.
	 */
	pasid_count = 1 << afu->config.pasid_supported_log;
	pasid_offset = ocxl_pasid_afu_alloc(fn, pasid_count);
	if (pasid_offset < 0) {
		dev_err(&pci_dev->dev, "Can't allocate %d PASIDs for AFU: %d\n",
			pasid_count, pasid_offset);
		return pasid_offset;
	}
	afu->pasid_base = fn->pasid_base + pasid_offset;
	afu->pasid_count = 0;
	afu->pasid_max = pasid_count;

	ocxl_config_set_afu_pasid(pci_dev, afu->config.dvsec_afu_control_pos,
				afu->pasid_base,
				afu->config.pasid_supported_log);
	dev_dbg(&pci_dev->dev, "PASID base=%d, enabled=%d\n",
		afu->pasid_base, pasid_count);
	return 0;
}