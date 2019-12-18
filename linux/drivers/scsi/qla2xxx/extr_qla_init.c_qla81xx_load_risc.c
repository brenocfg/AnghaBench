#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int running_gold_fw; } ;
struct qla_hw_data {TYPE_1__ flags; int /*<<< orphan*/  flt_region_gold_fw; int /*<<< orphan*/  flt_region_fw; int /*<<< orphan*/  flt_region_fw_sec; } ;
struct active_regions {scalar_t__ global; } ;
struct TYPE_10__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_QLA27XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA28XX (struct qla_hw_data*) ; 
 scalar_t__ QLA27XX_SECONDARY_IMAGE ; 
 int ql2xfwloadbin ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_2__*,int,char*) ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_2__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int qla24xx_load_risc_blob (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int qla24xx_load_risc_flash (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla27xx_get_active_image (TYPE_2__*,struct active_regions*) ; 

int
qla81xx_load_risc(scsi_qla_host_t *vha, uint32_t *srisc_addr)
{
	int rval;
	struct qla_hw_data *ha = vha->hw;
	struct active_regions active_regions = { };

	if (ql2xfwloadbin == 2)
		goto try_blob_fw;

	/* FW Load priority:
	 * 1) Firmware residing in flash.
	 * 2) Firmware via request-firmware interface (.bin file).
	 * 3) Golden-Firmware residing in flash -- (limited operation).
	 */

	if (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		goto try_primary_fw;

	qla27xx_get_active_image(vha, &active_regions);

	if (active_regions.global != QLA27XX_SECONDARY_IMAGE)
		goto try_primary_fw;

	ql_dbg(ql_dbg_init, vha, 0x008b,
	    "Loading secondary firmware image.\n");
	rval = qla24xx_load_risc_flash(vha, srisc_addr, ha->flt_region_fw_sec);
	if (!rval)
		return rval;

try_primary_fw:
	ql_dbg(ql_dbg_init, vha, 0x008b,
	    "Loading primary firmware image.\n");
	rval = qla24xx_load_risc_flash(vha, srisc_addr, ha->flt_region_fw);
	if (!rval)
		return rval;

try_blob_fw:
	rval = qla24xx_load_risc_blob(vha, srisc_addr);
	if (!rval || !ha->flt_region_gold_fw)
		return rval;

	ql_log(ql_log_info, vha, 0x0099,
	    "Attempting to fallback to golden firmware.\n");
	rval = qla24xx_load_risc_flash(vha, srisc_addr, ha->flt_region_gold_fw);
	if (rval)
		return rval;

	ql_log(ql_log_info, vha, 0x009a, "Need firmware flash update.\n");
	ha->flags.running_gold_fw = 1;
	return rval;
}