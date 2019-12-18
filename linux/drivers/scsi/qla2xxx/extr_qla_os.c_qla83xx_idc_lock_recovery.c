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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA83XX_DRIVER_LOCKID ; 
 unsigned long QLA83XX_MAX_LOCK_RECOVERY_WAIT ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 unsigned long jiffies ; 
 int qla83xx_force_lock_recovery (int /*<<< orphan*/ *) ; 
 int qla83xx_rd_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  qla83xx_wait_logic () ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static int
qla83xx_idc_lock_recovery(scsi_qla_host_t *base_vha)
{
	int rval = QLA_SUCCESS;
	uint32_t o_drv_lockid, n_drv_lockid;
	unsigned long lock_recovery_timeout;

	lock_recovery_timeout = jiffies + QLA83XX_MAX_LOCK_RECOVERY_WAIT;
retry_lockid:
	rval = qla83xx_rd_reg(base_vha, QLA83XX_DRIVER_LOCKID, &o_drv_lockid);
	if (rval)
		goto exit;

	/* MAX wait time before forcing IDC Lock recovery = 2 secs */
	if (time_after_eq(jiffies, lock_recovery_timeout)) {
		if (qla83xx_force_lock_recovery(base_vha) == QLA_SUCCESS)
			return QLA_SUCCESS;
		else
			return QLA_FUNCTION_FAILED;
	}

	rval = qla83xx_rd_reg(base_vha, QLA83XX_DRIVER_LOCKID, &n_drv_lockid);
	if (rval)
		goto exit;

	if (o_drv_lockid == n_drv_lockid) {
		qla83xx_wait_logic();
		goto retry_lockid;
	} else
		return QLA_SUCCESS;

exit:
	return rval;
}