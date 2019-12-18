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
struct ocxl_fn_config {scalar_t__ max_afu_index; int dvsec_afu_info_pos; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  OCXL_DVSEC_AFU_INFO_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int find_dvsec (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_dvsec_afu_info(struct pci_dev *dev, struct ocxl_fn_config *fn)
{
	int pos;

	if (fn->max_afu_index < 0) {
		fn->dvsec_afu_info_pos = -1;
		return 0;
	}

	pos = find_dvsec(dev, OCXL_DVSEC_AFU_INFO_ID);
	if (!pos) {
		dev_err(&dev->dev, "Can't find AFU information DVSEC\n");
		return -ENODEV;
	}
	fn->dvsec_afu_info_pos = pos;
	return 0;
}