#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_7__ {TYPE_1__* hw; int /*<<< orphan*/  fcport_waitQ; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_6__ {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_mark_all_devices_lost (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_fcport_count (TYPE_2__*) ; 
 scalar_t__ wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
qla2x00_wait_for_sess_deletion(scsi_qla_host_t *vha)
{
	u8 i;

	qla2x00_mark_all_devices_lost(vha, 0);

	for (i = 0; i < 10; i++) {
		if (wait_event_timeout(vha->fcport_waitQ,
		    test_fcport_count(vha), HZ) > 0)
			break;
	}

	flush_workqueue(vha->hw->wq);
}