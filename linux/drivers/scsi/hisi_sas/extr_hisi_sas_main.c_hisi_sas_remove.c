#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct Scsi_Host* shost; } ;
struct sas_ha_struct {TYPE_1__ core; struct hisi_hba* lldd_ha; } ;
struct platform_device {int dummy; } ;
struct hisi_hba {int /*<<< orphan*/  timer; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hisi_sas_free (struct hisi_hba*) ; 
 struct sas_ha_struct* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sas_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sas_unregister_ha (struct sas_ha_struct*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

int hisi_sas_remove(struct platform_device *pdev)
{
	struct sas_ha_struct *sha = platform_get_drvdata(pdev);
	struct hisi_hba *hisi_hba = sha->lldd_ha;
	struct Scsi_Host *shost = sha->core.shost;

	if (timer_pending(&hisi_hba->timer))
		del_timer(&hisi_hba->timer);

	sas_unregister_ha(sha);
	sas_remove_host(sha->core.shost);

	hisi_sas_free(hisi_hba);
	scsi_host_put(shost);
	return 0;
}