#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ vp_idx; int /*<<< orphan*/  dpc_flags; int /*<<< orphan*/  hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_11__ {int /*<<< orphan*/  state; TYPE_1__* vha; } ;
typedef  TYPE_3__ fc_port_t ;
struct TYPE_9__ {scalar_t__ vp_idx; } ;

/* Variables and functions */
 scalar_t__ FCS_DEVICE_DEAD ; 
 int /*<<< orphan*/  FCS_DEVICE_LOST ; 
 scalar_t__ FCS_ONLINE ; 
 scalar_t__ IS_QLAFX00 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELOGIN_NEEDED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla2x00_schedule_rport_del (TYPE_2__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  qla2x00_set_fcport_state (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qla2x00_mark_device_lost(scsi_qla_host_t *vha, fc_port_t *fcport,
    int do_login, int defer)
{
	if (IS_QLAFX00(vha->hw)) {
		qla2x00_set_fcport_state(fcport, FCS_DEVICE_LOST);
		qla2x00_schedule_rport_del(vha, fcport, defer);
		return;
	}

	if (atomic_read(&fcport->state) == FCS_ONLINE &&
	    vha->vp_idx == fcport->vha->vp_idx) {
		qla2x00_set_fcport_state(fcport, FCS_DEVICE_LOST);
		qla2x00_schedule_rport_del(vha, fcport, defer);
	}
	/*
	 * We may need to retry the login, so don't change the state of the
	 * port but do the retries.
	 */
	if (atomic_read(&fcport->state) != FCS_DEVICE_DEAD)
		qla2x00_set_fcport_state(fcport, FCS_DEVICE_LOST);

	if (!do_login)
		return;

	set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
}