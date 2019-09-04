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
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 scalar_t__ OCXL_DVSEC_VENDOR_CFG_VERS ; 
 scalar_t__ OCXL_DVSEC_VENDOR_DLX_VERS ; 
 int /*<<< orphan*/  OCXL_DVSEC_VENDOR_ID ; 
 scalar_t__ OCXL_DVSEC_VENDOR_TLX_VERS ; 
 scalar_t__ PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int find_dvsec (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_dvsec_vendor(struct pci_dev *dev)
{
	int pos;
	u32 cfg, tlx, dlx;

	/*
	 * vendor specific DVSEC is optional
	 *
	 * It's currently only used on function 0 to specify the
	 * version of some logic blocks. Some older images may not
	 * even have it so we ignore any errors
	 */
	if (PCI_FUNC(dev->devfn) != 0)
		return 0;

	pos = find_dvsec(dev, OCXL_DVSEC_VENDOR_ID);
	if (!pos)
		return 0;

	pci_read_config_dword(dev, pos + OCXL_DVSEC_VENDOR_CFG_VERS, &cfg);
	pci_read_config_dword(dev, pos + OCXL_DVSEC_VENDOR_TLX_VERS, &tlx);
	pci_read_config_dword(dev, pos + OCXL_DVSEC_VENDOR_DLX_VERS, &dlx);

	dev_dbg(&dev->dev, "Vendor specific DVSEC:\n");
	dev_dbg(&dev->dev, "  CFG version = 0x%x\n", cfg);
	dev_dbg(&dev->dev, "  TLX version = 0x%x\n", tlx);
	dev_dbg(&dev->dev, "  DLX version = 0x%x\n", dlx);
	return 0;
}