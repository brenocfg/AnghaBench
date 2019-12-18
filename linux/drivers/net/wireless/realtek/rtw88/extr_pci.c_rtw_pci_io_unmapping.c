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
struct rtw_pci {scalar_t__ mmap; } ;
struct rtw_dev {scalar_t__ priv; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 

__attribute__((used)) static void rtw_pci_io_unmapping(struct rtw_dev *rtwdev,
				 struct pci_dev *pdev)
{
	struct rtw_pci *rtwpci = (struct rtw_pci *)rtwdev->priv;

	if (rtwpci->mmap) {
		pci_iounmap(pdev, rtwpci->mmap);
		pci_release_regions(pdev);
	}
}