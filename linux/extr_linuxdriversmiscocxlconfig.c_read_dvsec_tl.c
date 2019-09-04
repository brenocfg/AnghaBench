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
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  devfn; } ;
struct ocxl_fn_config {int dvsec_tl_pos; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  OCXL_DVSEC_TL_ID ; 
 scalar_t__ PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int find_dvsec (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_dvsec_tl(struct pci_dev *dev, struct ocxl_fn_config *fn)
{
	int pos;

	pos = find_dvsec(dev, OCXL_DVSEC_TL_ID);
	if (!pos && PCI_FUNC(dev->devfn) == 0) {
		dev_err(&dev->dev, "Can't find TL DVSEC\n");
		return -ENODEV;
	}
	if (pos && PCI_FUNC(dev->devfn) != 0) {
		dev_err(&dev->dev, "TL DVSEC is only allowed on function 0\n");
		return -ENODEV;
	}
	fn->dvsec_tl_pos = pos;
	return 0;
}