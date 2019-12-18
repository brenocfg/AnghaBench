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
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 unsigned long HZ ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sas_drain_work (struct sas_ha_struct*) ; 

int pm8001_scan_finished(struct Scsi_Host *shost, unsigned long time)
{
	struct sas_ha_struct *ha = SHOST_TO_SAS_HA(shost);

	/* give the phy enabling interrupt event time to come in (1s
	* is empirically about all it takes) */
	if (time < HZ)
		return 0;
	/* Wait for discovery to finish */
	sas_drain_work(ha);
	return 1;
}