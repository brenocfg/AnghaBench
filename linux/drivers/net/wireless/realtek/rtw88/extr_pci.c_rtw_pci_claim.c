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
struct rtw_dev {int /*<<< orphan*/  hw; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_IEEE80211_DEV (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 

__attribute__((used)) static int rtw_pci_claim(struct rtw_dev *rtwdev, struct pci_dev *pdev)
{
	int ret;

	ret = pci_enable_device(pdev);
	if (ret) {
		rtw_err(rtwdev, "failed to enable pci device\n");
		return ret;
	}

	pci_set_master(pdev);
	pci_set_drvdata(pdev, rtwdev->hw);
	SET_IEEE80211_DEV(rtwdev->hw, &pdev->dev);

	return 0;
}