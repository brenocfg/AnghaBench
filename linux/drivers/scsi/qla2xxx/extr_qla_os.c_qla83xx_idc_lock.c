#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct qla_hw_data {int /*<<< orphan*/  portnum; } ;
struct TYPE_8__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA83XX_DRIVER_LOCK ; 
 int /*<<< orphan*/  QLA83XX_DRIVER_LOCKID ; 
 scalar_t__ QLA_SUCCESS ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_1__*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  ql_dbg_p3p ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 scalar_t__ qla83xx_idc_lock_recovery (TYPE_1__*) ; 
 scalar_t__ qla83xx_rd_reg (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  qla83xx_wait_logic () ; 
 int /*<<< orphan*/  qla83xx_wr_reg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
qla83xx_idc_lock(scsi_qla_host_t *base_vha, uint16_t requester_id)
{
	uint32_t data;
	uint32_t lock_owner;
	struct qla_hw_data *ha = base_vha->hw;

	/* IDC-lock implementation using driver-lock/lock-id remote registers */
retry_lock:
	if (qla83xx_rd_reg(base_vha, QLA83XX_DRIVER_LOCK, &data)
	    == QLA_SUCCESS) {
		if (data) {
			/* Setting lock-id to our function-number */
			qla83xx_wr_reg(base_vha, QLA83XX_DRIVER_LOCKID,
			    ha->portnum);
		} else {
			qla83xx_rd_reg(base_vha, QLA83XX_DRIVER_LOCKID,
			    &lock_owner);
			ql_dbg(ql_dbg_p3p, base_vha, 0xb063,
			    "Failed to acquire IDC lock, acquired by %d, "
			    "retrying...\n", lock_owner);

			/* Retry/Perform IDC-Lock recovery */
			if (qla83xx_idc_lock_recovery(base_vha)
			    == QLA_SUCCESS) {
				qla83xx_wait_logic();
				goto retry_lock;
			} else
				ql_log(ql_log_warn, base_vha, 0xb075,
				    "IDC Lock recovery FAILED.\n");
		}

	}

	return;
}