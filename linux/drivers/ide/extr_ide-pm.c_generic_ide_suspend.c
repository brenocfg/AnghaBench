#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct request {int dummy; } ;
struct ide_pm_state {scalar_t__ pm_state; int /*<<< orphan*/  pm_step; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  rqpm ;
struct TYPE_9__ {scalar_t__ event; } ;
typedef  TYPE_1__ pm_message_t ;
typedef  int /*<<< orphan*/  ide_hwif_t ;
struct TYPE_10__ {int dn; int /*<<< orphan*/  queue; int /*<<< orphan*/ * hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_12__ {struct ide_pm_state* special; int /*<<< orphan*/  type; } ;
struct TYPE_11__ {scalar_t__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_PRIV_PM_SUSPEND ; 
 int EIO ; 
 int /*<<< orphan*/  IDE_PM_START_SUSPEND ; 
 scalar_t__ PM_EVENT_FREEZE ; 
 scalar_t__ PM_EVENT_PRETHAW ; 
 int /*<<< orphan*/  REQ_OP_DRV_IN ; 
 int /*<<< orphan*/  blk_execute_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_get_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int /*<<< orphan*/  ide_acpi_get_timing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ide_acpi_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* ide_get_pair_dev (TYPE_2__*) ; 
 scalar_t__ ide_port_acpi (int /*<<< orphan*/ *) ; 
 TYPE_5__* ide_req (struct request*) ; 
 int /*<<< orphan*/  memset (struct ide_pm_state*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* scsi_req (struct request*) ; 
 TYPE_2__* to_ide_device (struct device*) ; 

int generic_ide_suspend(struct device *dev, pm_message_t mesg)
{
	ide_drive_t *drive = to_ide_device(dev);
	ide_drive_t *pair = ide_get_pair_dev(drive);
	ide_hwif_t *hwif = drive->hwif;
	struct request *rq;
	struct ide_pm_state rqpm;
	int ret;

	if (ide_port_acpi(hwif)) {
		/* call ACPI _GTM only once */
		if ((drive->dn & 1) == 0 || pair == NULL)
			ide_acpi_get_timing(hwif);
	}

	memset(&rqpm, 0, sizeof(rqpm));
	rq = blk_get_request(drive->queue, REQ_OP_DRV_IN, 0);
	ide_req(rq)->type = ATA_PRIV_PM_SUSPEND;
	ide_req(rq)->special = &rqpm;
	rqpm.pm_step = IDE_PM_START_SUSPEND;
	if (mesg.event == PM_EVENT_PRETHAW)
		mesg.event = PM_EVENT_FREEZE;
	rqpm.pm_state = mesg.event;

	blk_execute_rq(drive->queue, NULL, rq, 0);
	ret = scsi_req(rq)->result ? -EIO : 0;
	blk_put_request(rq);

	if (ret == 0 && ide_port_acpi(hwif)) {
		/* call ACPI _PS3 only after both devices are suspended */
		if ((drive->dn & 1) || pair == NULL)
			ide_acpi_set_state(hwif, 0);
	}

	return ret;
}