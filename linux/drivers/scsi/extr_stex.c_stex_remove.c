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
struct st_hba {int /*<<< orphan*/  host; int /*<<< orphan*/  mu_status; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_NO_CONNECT ; 
 int /*<<< orphan*/  MU_STATE_NOCONNECT ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct st_hba* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  return_abnormal_state (struct st_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_block_requests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stex_hba_free (struct st_hba*) ; 
 int /*<<< orphan*/  stex_notifier ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stex_remove(struct pci_dev *pdev)
{
	struct st_hba *hba = pci_get_drvdata(pdev);

	hba->mu_status = MU_STATE_NOCONNECT;
	return_abnormal_state(hba, DID_NO_CONNECT);
	scsi_remove_host(hba->host);

	scsi_block_requests(hba->host);

	stex_hba_free(hba);

	scsi_host_put(hba->host);

	pci_disable_device(pdev);

	unregister_reboot_notifier(&stex_notifier);
}