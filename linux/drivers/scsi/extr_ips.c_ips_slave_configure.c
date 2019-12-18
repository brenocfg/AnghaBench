#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {scalar_t__ type; int skip_ms_page_8; int skip_ms_page_3f; scalar_t__ tagged_supported; int /*<<< orphan*/  host; } ;
struct TYPE_5__ {int max_cmds; TYPE_1__* enq; } ;
typedef  TYPE_2__ ips_ha_t ;
struct TYPE_4__ {int ucLogDriveCount; } ;

/* Variables and functions */
 TYPE_2__* IPS_HA (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_DISK ; 
 int /*<<< orphan*/  scsi_change_queue_depth (struct scsi_device*,int) ; 

__attribute__((used)) static int
ips_slave_configure(struct scsi_device * SDptr)
{
	ips_ha_t *ha;
	int min;

	ha = IPS_HA(SDptr->host);
	if (SDptr->tagged_supported && SDptr->type == TYPE_DISK) {
		min = ha->max_cmds / 2;
		if (ha->enq->ucLogDriveCount <= 2)
			min = ha->max_cmds - 1;
		scsi_change_queue_depth(SDptr, min);
	}

	SDptr->skip_ms_page_8 = 1;
	SDptr->skip_ms_page_3f = 1;
	return 0;
}