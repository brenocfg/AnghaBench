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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ocxl_fn_config {int dvsec_function_pos; int max_afu_index; } ;

/* Variables and functions */
 int ENODEV ; 
 int EXTRACT_BIT (int /*<<< orphan*/ ,int) ; 
 int EXTRACT_BITS (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  OCXL_DVSEC_FUNC_ID ; 
 scalar_t__ OCXL_DVSEC_FUNC_OFF_INDEX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int find_dvsec (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_dvsec_function(struct pci_dev *dev, struct ocxl_fn_config *fn)
{
	int pos, afu_present;
	u32 val;

	pos = find_dvsec(dev, OCXL_DVSEC_FUNC_ID);
	if (!pos) {
		dev_err(&dev->dev, "Can't find function DVSEC\n");
		return -ENODEV;
	}
	fn->dvsec_function_pos = pos;

	pci_read_config_dword(dev, pos + OCXL_DVSEC_FUNC_OFF_INDEX, &val);
	afu_present = EXTRACT_BIT(val, 31);
	if (!afu_present) {
		fn->max_afu_index = -1;
		dev_dbg(&dev->dev, "Function doesn't define any AFU\n");
		goto out;
	}
	fn->max_afu_index = EXTRACT_BITS(val, 24, 29);

out:
	dev_dbg(&dev->dev, "Function DVSEC:\n");
	dev_dbg(&dev->dev, "  Max AFU index = %d\n", fn->max_afu_index);
	return 0;
}