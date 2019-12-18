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
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLA8044_CRB_TEMP_STATE_INDEX ; 
 scalar_t__ QLA82XX_TEMP_PANIC ; 
 scalar_t__ QLA82XX_TEMP_WARN ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 scalar_t__ qla8044_rd_direct (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 scalar_t__ qla82xx_get_temp_state (scalar_t__) ; 
 scalar_t__ qla82xx_get_temp_val (scalar_t__) ; 

__attribute__((used)) static int
qla8044_check_temp(struct scsi_qla_host *vha)
{
	uint32_t temp, temp_state, temp_val;
	int status = QLA_SUCCESS;

	temp = qla8044_rd_direct(vha, QLA8044_CRB_TEMP_STATE_INDEX);
	temp_state = qla82xx_get_temp_state(temp);
	temp_val = qla82xx_get_temp_val(temp);

	if (temp_state == QLA82XX_TEMP_PANIC) {
		ql_log(ql_log_warn, vha, 0xb0d2,
		    "Device temperature %d degrees C"
		    " exceeds maximum allowed. Hardware has been shut"
		    " down\n", temp_val);
		status = QLA_FUNCTION_FAILED;
		return status;
	} else if (temp_state == QLA82XX_TEMP_WARN) {
		ql_log(ql_log_warn, vha, 0xb0d3,
		    "Device temperature %d"
		    " degrees C exceeds operating range."
		    " Immediate action needed.\n", temp_val);
	}
	return 0;
}