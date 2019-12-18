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
struct cxgbi_hba {int /*<<< orphan*/  shost; } ;
struct cxgbi_device {int nports; int /*<<< orphan*/  pdev; struct cxgbi_hba** hbas; } ;

/* Variables and functions */
 int CXGBI_DBG_DEV ; 
 int /*<<< orphan*/  iscsi_host_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_host_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_device*,int) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 

void cxgbi_hbas_remove(struct cxgbi_device *cdev)
{
	int i;
	struct cxgbi_hba *chba;

	log_debug(1 << CXGBI_DBG_DEV,
		"cdev 0x%p, p#%u.\n", cdev, cdev->nports);

	for (i = 0; i < cdev->nports; i++) {
		chba = cdev->hbas[i];
		if (chba) {
			cdev->hbas[i] = NULL;
			iscsi_host_remove(chba->shost);
			pci_dev_put(cdev->pdev);
			iscsi_host_free(chba->shost);
		}
	}
}