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
typedef  int /*<<< orphan*/  uint64_t ;
struct pnv_phb {int /*<<< orphan*/  opal_id; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;
struct pci_controller {struct pnv_phb* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int PNV_OCXL_TL_RATE_BUF_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int opal_npu_tl_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,int) ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 

int pnv_ocxl_set_tl_conf(struct pci_dev *dev, long cap,
			uint64_t rate_buf_phys, int rate_buf_size)
{
	struct pci_controller *hose = pci_bus_to_host(dev->bus);
	struct pnv_phb *phb = hose->private_data;
	int rc;

	if (rate_buf_size != PNV_OCXL_TL_RATE_BUF_SIZE)
		return -EINVAL;

	rc = opal_npu_tl_set(phb->opal_id, dev->devfn, cap,
			rate_buf_phys, rate_buf_size);
	if (rc) {
		dev_err(&dev->dev, "Can't configure host TL: %d\n", rc);
		return -EINVAL;
	}
	return 0;
}