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
typedef  int /*<<< orphan*/  u64 ;
struct zfcp_unit {int /*<<< orphan*/  fcp_lun; TYPE_1__* port; } ;
struct scsi_lun {int dummy; } ;
struct fc_rport {scalar_t__ port_state; int /*<<< orphan*/  scsi_target_id; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct fc_rport* rport; } ;

/* Variables and functions */
 scalar_t__ FC_PORTSTATE_ONLINE ; 
 int /*<<< orphan*/  SCSI_SCAN_MANUAL ; 
 int /*<<< orphan*/  scsi_scan_target (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsilun_to_int (struct scsi_lun*) ; 

void zfcp_unit_scsi_scan(struct zfcp_unit *unit)
{
	struct fc_rport *rport = unit->port->rport;
	u64 lun;

	lun = scsilun_to_int((struct scsi_lun *) &unit->fcp_lun);

	if (rport && rport->port_state == FC_PORTSTATE_ONLINE)
		scsi_scan_target(&rport->dev, 0, rport->scsi_target_id, lun,
				 SCSI_SCAN_MANUAL);
}