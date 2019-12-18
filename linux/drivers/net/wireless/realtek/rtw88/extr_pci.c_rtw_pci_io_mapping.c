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
typedef  int u8 ;
struct rtw_pci {int /*<<< orphan*/  mmap; } ;
struct rtw_dev {scalar_t__ priv; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  pci_iomap (struct pci_dev*,int,unsigned long) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 unsigned long pci_resource_len (struct pci_dev*,int) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 

__attribute__((used)) static int rtw_pci_io_mapping(struct rtw_dev *rtwdev,
			      struct pci_dev *pdev)
{
	struct rtw_pci *rtwpci = (struct rtw_pci *)rtwdev->priv;
	unsigned long len;
	u8 bar_id = 2;
	int ret;

	ret = pci_request_regions(pdev, KBUILD_MODNAME);
	if (ret) {
		rtw_err(rtwdev, "failed to request pci regions\n");
		return ret;
	}

	len = pci_resource_len(pdev, bar_id);
	rtwpci->mmap = pci_iomap(pdev, bar_id, len);
	if (!rtwpci->mmap) {
		rtw_err(rtwdev, "failed to map pci memory\n");
		return -ENOMEM;
	}

	return 0;
}