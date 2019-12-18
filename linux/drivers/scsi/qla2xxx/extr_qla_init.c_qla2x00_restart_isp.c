#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int chip_reset_done; } ;
struct qla_hw_data {int /*<<< orphan*/  base_qpair; TYPE_3__ flags; TYPE_2__* isp_ops; } ;
struct TYPE_12__ {scalar_t__ online; } ;
struct TYPE_15__ {int device_flags; int /*<<< orphan*/  dpc_flags; TYPE_1__ flags; struct qla_hw_data* hw; } ;
typedef  TYPE_4__ scsi_qla_host_t ;
struct TYPE_13__ {int (* chip_diag ) (TYPE_4__*) ;} ;

/* Variables and functions */
 int DFLG_NO_CABLE ; 
 int /*<<< orphan*/  LOOP_RESYNC_NEEDED ; 
 int /*<<< orphan*/  MK_SYNC_ALL ; 
 int /*<<< orphan*/  RESET_MARKER_NEEDED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla25xx_init_queues (struct qla_hw_data*) ; 
 int qla2x00_fw_ready (TYPE_4__*) ; 
 int qla2x00_init_rings (TYPE_4__*) ; 
 scalar_t__ qla2x00_isp_firmware (TYPE_4__*) ; 
 int /*<<< orphan*/  qla2x00_marker (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qla2x00_setup_chip (TYPE_4__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_4__*) ; 

__attribute__((used)) static int
qla2x00_restart_isp(scsi_qla_host_t *vha)
{
	int status = 0;
	struct qla_hw_data *ha = vha->hw;

	/* If firmware needs to be loaded */
	if (qla2x00_isp_firmware(vha)) {
		vha->flags.online = 0;
		status = ha->isp_ops->chip_diag(vha);
		if (!status)
			status = qla2x00_setup_chip(vha);
	}

	if (!status && !(status = qla2x00_init_rings(vha))) {
		clear_bit(RESET_MARKER_NEEDED, &vha->dpc_flags);
		ha->flags.chip_reset_done = 1;

		/* Initialize the queues in use */
		qla25xx_init_queues(ha);

		status = qla2x00_fw_ready(vha);
		if (!status) {
			/* Issue a marker after FW becomes ready. */
			qla2x00_marker(vha, ha->base_qpair, 0, 0, MK_SYNC_ALL);
			set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
		}

		/* if no cable then assume it's good */
		if ((vha->device_flags & DFLG_NO_CABLE))
			status = 0;
	}
	return (status);
}