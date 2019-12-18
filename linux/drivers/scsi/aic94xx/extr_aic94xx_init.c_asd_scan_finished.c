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
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sas_drain_work (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asd_scan_finished(struct Scsi_Host *shost, unsigned long time)
{
	/* give the phy enabling interrupt event time to come in (1s
	 * is empirically about all it takes) */
	if (time < HZ)
		return 0;
	/* Wait for discovery to finish */
	sas_drain_work(SHOST_TO_SAS_HA(shost));
	return 1;
}