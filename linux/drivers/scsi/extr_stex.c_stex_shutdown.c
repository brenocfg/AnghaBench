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
struct st_hba {int supports_pm; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ S6flag ; 
 int /*<<< orphan*/  ST_IGNORED ; 
 int /*<<< orphan*/  ST_S5 ; 
 int /*<<< orphan*/  ST_S6 ; 
 struct st_hba* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  stex_hba_stop (struct st_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stex_notifier ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stex_shutdown(struct pci_dev *pdev)
{
	struct st_hba *hba = pci_get_drvdata(pdev);

	if (hba->supports_pm == 0) {
		stex_hba_stop(hba, ST_IGNORED);
	} else if (hba->supports_pm == 1 && S6flag) {
		unregister_reboot_notifier(&stex_notifier);
		stex_hba_stop(hba, ST_S6);
	} else
		stex_hba_stop(hba, ST_S5);
}