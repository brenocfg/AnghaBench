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
struct ocxl_fn {int actag_enabled; int actag_supported; scalar_t__ actag_base; } ;
struct TYPE_2__ {int actag_supported; int /*<<< orphan*/  dvsec_afu_control_pos; } ;
struct ocxl_afu {int actag_enabled; scalar_t__ actag_base; int /*<<< orphan*/  dev; TYPE_1__ config; struct ocxl_fn* fn; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int ocxl_actag_afu_alloc (struct ocxl_fn*,int) ; 
 int /*<<< orphan*/  ocxl_config_set_afu_actag (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int assign_afu_actag(struct ocxl_afu *afu, struct pci_dev *dev)
{
	struct ocxl_fn *fn = afu->fn;
	int actag_count, actag_offset;

	/*
	 * if there were not enough actags for the function, each afu
	 * reduces its count as well
	 */
	actag_count = afu->config.actag_supported *
		fn->actag_enabled / fn->actag_supported;
	actag_offset = ocxl_actag_afu_alloc(fn, actag_count);
	if (actag_offset < 0) {
		dev_err(&afu->dev, "Can't allocate %d actags for AFU: %d\n",
			actag_count, actag_offset);
		return actag_offset;
	}
	afu->actag_base = fn->actag_base + actag_offset;
	afu->actag_enabled = actag_count;

	ocxl_config_set_afu_actag(dev, afu->config.dvsec_afu_control_pos,
				afu->actag_base, afu->actag_enabled);
	dev_dbg(&afu->dev, "actag base=%d enabled=%d\n",
		afu->actag_base, afu->actag_enabled);
	return 0;
}