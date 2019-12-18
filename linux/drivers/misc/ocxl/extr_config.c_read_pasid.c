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
struct ocxl_fn_config {int max_pasid_log; } ;

/* Variables and functions */
 int EXTRACT_BITS (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_PASID ; 
 scalar_t__ PCI_PASID_CAP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_pasid(struct pci_dev *dev, struct ocxl_fn_config *fn)
{
	u16 val;
	int pos;

	pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_PASID);
	if (!pos) {
		/*
		 * PASID capability is not mandatory, but there
		 * shouldn't be any AFU
		 */
		dev_dbg(&dev->dev, "Function doesn't require any PASID\n");
		fn->max_pasid_log = -1;
		goto out;
	}
	pci_read_config_word(dev, pos + PCI_PASID_CAP, &val);
	fn->max_pasid_log = EXTRACT_BITS(val, 8, 12);

out:
	dev_dbg(&dev->dev, "PASID capability:\n");
	dev_dbg(&dev->dev, "  Max PASID log = %d\n", fn->max_pasid_log);
}