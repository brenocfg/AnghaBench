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
struct rtw_pci {struct pci_dev* pdev; } ;
struct rtw_dev {scalar_t__ priv; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 
 int rtw_pci_init (struct rtw_dev*) ; 
 int rtw_pci_io_mapping (struct rtw_dev*,struct pci_dev*) ; 
 int /*<<< orphan*/  rtw_pci_io_unmapping (struct rtw_dev*,struct pci_dev*) ; 
 int /*<<< orphan*/  rtw_pci_phy_cfg (struct rtw_dev*) ; 

__attribute__((used)) static int rtw_pci_setup_resource(struct rtw_dev *rtwdev, struct pci_dev *pdev)
{
	struct rtw_pci *rtwpci;
	int ret;

	rtwpci = (struct rtw_pci *)rtwdev->priv;
	rtwpci->pdev = pdev;

	/* after this driver can access to hw registers */
	ret = rtw_pci_io_mapping(rtwdev, pdev);
	if (ret) {
		rtw_err(rtwdev, "failed to request pci io region\n");
		goto err_out;
	}

	ret = rtw_pci_init(rtwdev);
	if (ret) {
		rtw_err(rtwdev, "failed to allocate pci resources\n");
		goto err_io_unmap;
	}

	rtw_pci_phy_cfg(rtwdev);

	return 0;

err_io_unmap:
	rtw_pci_io_unmapping(rtwdev, pdev);

err_out:
	return ret;
}