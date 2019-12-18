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
typedef  int u32 ;
struct sis_sync_cmd_params {int* mailbox; } ;
struct pqi_ctrl_info {int pqi_reset_quiesce_supported; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SIS_CMD_GET_ADAPTER_PROPERTIES ; 
 int SIS_EXTENDED_PROPERTIES_SUPPORTED ; 
 int SIS_PQI_RESET_QUIESCE_SUPPORTED ; 
 int SIS_REQUIRED_EXTENDED_PROPERTIES ; 
 int /*<<< orphan*/  memset (struct sis_sync_cmd_params*,int /*<<< orphan*/ ,int) ; 
 int sis_send_sync_cmd (struct pqi_ctrl_info*,int /*<<< orphan*/ ,struct sis_sync_cmd_params*) ; 

int sis_get_ctrl_properties(struct pqi_ctrl_info *ctrl_info)
{
	int rc;
	u32 properties;
	u32 extended_properties;
	struct sis_sync_cmd_params params;

	memset(&params, 0, sizeof(params));

	rc = sis_send_sync_cmd(ctrl_info, SIS_CMD_GET_ADAPTER_PROPERTIES,
		&params);
	if (rc)
		return rc;

	properties = params.mailbox[1];

	if (!(properties & SIS_EXTENDED_PROPERTIES_SUPPORTED))
		return -ENODEV;

	extended_properties = params.mailbox[4];

	if ((extended_properties & SIS_REQUIRED_EXTENDED_PROPERTIES) !=
		SIS_REQUIRED_EXTENDED_PROPERTIES)
		return -ENODEV;

	if (extended_properties & SIS_PQI_RESET_QUIESCE_SUPPORTED)
		ctrl_info->pqi_reset_quiesce_supported = true;

	return 0;
}