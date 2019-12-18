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
struct Scsi_Host {int host_no; int /*<<< orphan*/ * work_q; int /*<<< orphan*/  work_q_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SNIC_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNIC_HOST_ERR (struct Scsi_Host*,char*,...) ; 
 int /*<<< orphan*/ * create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int
snic_add_host(struct Scsi_Host *shost, struct pci_dev *pdev)
{
	int ret = 0;

	ret = scsi_add_host(shost, &pdev->dev);
	if (ret) {
		SNIC_HOST_ERR(shost,
			      "snic: scsi_add_host failed. %d\n",
			      ret);

		return ret;
	}

	SNIC_BUG_ON(shost->work_q != NULL);
	snprintf(shost->work_q_name, sizeof(shost->work_q_name), "scsi_wq_%d",
		 shost->host_no);
	shost->work_q = create_singlethread_workqueue(shost->work_q_name);
	if (!shost->work_q) {
		SNIC_HOST_ERR(shost, "Failed to Create ScsiHost wq.\n");

		ret = -ENOMEM;
	}

	return ret;
}