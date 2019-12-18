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
struct pci_dev {int dummy; } ;
struct ci_hdrc_pci {int /*<<< orphan*/  phy; int /*<<< orphan*/  ci; } ;

/* Variables and functions */
 int /*<<< orphan*/  ci_hdrc_remove_device (int /*<<< orphan*/ ) ; 
 struct ci_hdrc_pci* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  usb_phy_generic_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ci_hdrc_pci_remove(struct pci_dev *pdev)
{
	struct ci_hdrc_pci *ci = pci_get_drvdata(pdev);

	ci_hdrc_remove_device(ci->ci);
	usb_phy_generic_unregister(ci->phy);
}