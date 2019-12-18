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
struct sas_ha_struct {struct isci_host* lldd_ha; } ;
struct isci_host {int /*<<< orphan*/  flags; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IHOST_START_PENDING ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sas_drain_work (struct sas_ha_struct*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int isci_host_scan_finished(struct Scsi_Host *shost, unsigned long time)
{
	struct sas_ha_struct *ha = SHOST_TO_SAS_HA(shost);
	struct isci_host *ihost = ha->lldd_ha;

	if (test_bit(IHOST_START_PENDING, &ihost->flags))
		return 0;

	sas_drain_work(ha);

	return 1;
}