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
struct sas_ha_struct {int dummy; } ;
struct hisi_hba {struct sas_ha_struct sha; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  sas_drain_work (struct sas_ha_struct*) ; 
 struct hisi_hba* shost_priv (struct Scsi_Host*) ; 

int hisi_sas_scan_finished(struct Scsi_Host *shost, unsigned long time)
{
	struct hisi_hba *hisi_hba = shost_priv(shost);
	struct sas_ha_struct *sha = &hisi_hba->sha;

	/* Wait for PHY up interrupt to occur */
	if (time < HZ)
		return 0;

	sas_drain_work(sha);
	return 1;
}