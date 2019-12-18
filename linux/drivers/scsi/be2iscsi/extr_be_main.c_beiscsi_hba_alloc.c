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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct beiscsi_hba {int interface_handle; int /*<<< orphan*/  pcidev; struct Scsi_Host* shost; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  max_cmd_len; scalar_t__ max_channel; int /*<<< orphan*/  max_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE2_MAX_SESSIONS ; 
 int /*<<< orphan*/  BEISCSI_MAX_CMD_LEN ; 
 int /*<<< orphan*/  BEISCSI_NUM_MAX_LUN ; 
 int /*<<< orphan*/  beiscsi_scsi_transport ; 
 int /*<<< orphan*/  beiscsi_sht ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct Scsi_Host* iscsi_host_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct beiscsi_hba* iscsi_host_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  memset (struct beiscsi_hba*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_dev_get (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct beiscsi_hba*) ; 

__attribute__((used)) static struct beiscsi_hba *beiscsi_hba_alloc(struct pci_dev *pcidev)
{
	struct beiscsi_hba *phba;
	struct Scsi_Host *shost;

	shost = iscsi_host_alloc(&beiscsi_sht, sizeof(*phba), 0);
	if (!shost) {
		dev_err(&pcidev->dev,
			"beiscsi_hba_alloc - iscsi_host_alloc failed\n");
		return NULL;
	}
	shost->max_id = BE2_MAX_SESSIONS;
	shost->max_channel = 0;
	shost->max_cmd_len = BEISCSI_MAX_CMD_LEN;
	shost->max_lun = BEISCSI_NUM_MAX_LUN;
	shost->transportt = beiscsi_scsi_transport;
	phba = iscsi_host_priv(shost);
	memset(phba, 0, sizeof(*phba));
	phba->shost = shost;
	phba->pcidev = pci_dev_get(pcidev);
	pci_set_drvdata(pcidev, phba);
	phba->interface_handle = 0xFFFFFFFF;

	return phba;
}