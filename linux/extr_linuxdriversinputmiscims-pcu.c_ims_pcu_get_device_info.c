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
struct ims_pcu {int* cmd_buf; int /*<<< orphan*/  reset_reason; int /*<<< orphan*/  bl_version; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  serial_number; int /*<<< orphan*/  date_of_manufacturing; int /*<<< orphan*/  part_number; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_BL_VERSION ; 
 int /*<<< orphan*/  GET_FW_VERSION ; 
 size_t IMS_PCU_DATA_OFFSET ; 
 int /*<<< orphan*/  RESET_REASON ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int ims_pcu_execute_query (struct ims_pcu*,int /*<<< orphan*/ ) ; 
 int ims_pcu_get_info (struct ims_pcu*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,...) ; 

__attribute__((used)) static int ims_pcu_get_device_info(struct ims_pcu *pcu)
{
	int error;

	error = ims_pcu_get_info(pcu);
	if (error)
		return error;

	error = ims_pcu_execute_query(pcu, GET_FW_VERSION);
	if (error) {
		dev_err(pcu->dev,
			"GET_FW_VERSION command failed, error: %d\n", error);
		return error;
	}

	snprintf(pcu->fw_version, sizeof(pcu->fw_version),
		 "%02d%02d%02d%02d.%c%c",
		 pcu->cmd_buf[2], pcu->cmd_buf[3], pcu->cmd_buf[4], pcu->cmd_buf[5],
		 pcu->cmd_buf[6], pcu->cmd_buf[7]);

	error = ims_pcu_execute_query(pcu, GET_BL_VERSION);
	if (error) {
		dev_err(pcu->dev,
			"GET_BL_VERSION command failed, error: %d\n", error);
		return error;
	}

	snprintf(pcu->bl_version, sizeof(pcu->bl_version),
		 "%02d%02d%02d%02d.%c%c",
		 pcu->cmd_buf[2], pcu->cmd_buf[3], pcu->cmd_buf[4], pcu->cmd_buf[5],
		 pcu->cmd_buf[6], pcu->cmd_buf[7]);

	error = ims_pcu_execute_query(pcu, RESET_REASON);
	if (error) {
		dev_err(pcu->dev,
			"RESET_REASON command failed, error: %d\n", error);
		return error;
	}

	snprintf(pcu->reset_reason, sizeof(pcu->reset_reason),
		 "%02x", pcu->cmd_buf[IMS_PCU_DATA_OFFSET]);

	dev_dbg(pcu->dev,
		"P/N: %s, MD: %s, S/N: %s, FW: %s, BL: %s, RR: %s\n",
		pcu->part_number,
		pcu->date_of_manufacturing,
		pcu->serial_number,
		pcu->fw_version,
		pcu->bl_version,
		pcu->reset_reason);

	return 0;
}