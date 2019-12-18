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
struct hisi_hba {int /*<<< orphan*/  rst_work; int /*<<< orphan*/  wq; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int SCSI_ADAPTER_RESET ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hisi_hba* shost_priv (struct Scsi_Host*) ; 

int hisi_sas_host_reset(struct Scsi_Host *shost, int reset_type)
{
	struct hisi_hba *hisi_hba = shost_priv(shost);

	if (reset_type != SCSI_ADAPTER_RESET)
		return -EOPNOTSUPP;

	queue_work(hisi_hba->wq, &hisi_hba->rst_work);

	return 0;
}