#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct mwifiex_scan_cmd_config {int tlv_buf_len; int /*<<< orphan*/  tlv_buf; int /*<<< orphan*/  specific_bssid; int /*<<< orphan*/  bss_mode; } ;
struct host_cmd_ds_802_11_scan {int /*<<< orphan*/  tlv_buffer; int /*<<< orphan*/  bssid; int /*<<< orphan*/  bss_mode; } ;
struct TYPE_2__ {struct host_cmd_ds_802_11_scan scan; } ;
struct host_cmd_ds_command {void* size; void* command; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  HostCmd_CMD_802_11_SCAN ; 
 scalar_t__ S_DS_GEN ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int mwifiex_cmd_802_11_scan(struct host_cmd_ds_command *cmd,
			    struct mwifiex_scan_cmd_config *scan_cfg)
{
	struct host_cmd_ds_802_11_scan *scan_cmd = &cmd->params.scan;

	/* Set fixed field variables in scan command */
	scan_cmd->bss_mode = scan_cfg->bss_mode;
	memcpy(scan_cmd->bssid, scan_cfg->specific_bssid,
	       sizeof(scan_cmd->bssid));
	memcpy(scan_cmd->tlv_buffer, scan_cfg->tlv_buf, scan_cfg->tlv_buf_len);

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_SCAN);

	/* Size is equal to the sizeof(fixed portions) + the TLV len + header */
	cmd->size = cpu_to_le16((u16) (sizeof(scan_cmd->bss_mode)
					  + sizeof(scan_cmd->bssid)
					  + scan_cfg->tlv_buf_len + S_DS_GEN));

	return 0;
}