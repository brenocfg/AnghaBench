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
struct sev_user_data_status {int dummy; } ;
struct sev_data_send_update_vmsa {int dummy; } ;
struct sev_data_send_update_data {int dummy; } ;
struct sev_data_send_start {int dummy; } ;
struct sev_data_send_finish {int dummy; } ;
struct sev_data_receive_update_vmsa {int dummy; } ;
struct sev_data_receive_update_data {int dummy; } ;
struct sev_data_receive_start {int dummy; } ;
struct sev_data_receive_finish {int dummy; } ;
struct sev_data_pek_csr {int dummy; } ;
struct sev_data_pek_cert_import {int dummy; } ;
struct sev_data_pdh_cert_export {int dummy; } ;
struct sev_data_launch_update_vmsa {int dummy; } ;
struct sev_data_launch_update_data {int dummy; } ;
struct sev_data_launch_start {int dummy; } ;
struct sev_data_launch_secret {int dummy; } ;
struct sev_data_launch_measure {int dummy; } ;
struct sev_data_launch_finish {int dummy; } ;
struct sev_data_init {int dummy; } ;
struct sev_data_guest_status {int dummy; } ;
struct sev_data_get_id {int dummy; } ;
struct sev_data_download_firmware {int dummy; } ;
struct sev_data_decommission {int dummy; } ;
struct sev_data_deactivate {int dummy; } ;
struct sev_data_dbg {int dummy; } ;
struct sev_data_activate {int dummy; } ;

/* Variables and functions */
#define  SEV_CMD_ACTIVATE 154 
#define  SEV_CMD_DBG_DECRYPT 153 
#define  SEV_CMD_DBG_ENCRYPT 152 
#define  SEV_CMD_DEACTIVATE 151 
#define  SEV_CMD_DECOMMISSION 150 
#define  SEV_CMD_DOWNLOAD_FIRMWARE 149 
#define  SEV_CMD_GET_ID 148 
#define  SEV_CMD_GUEST_STATUS 147 
#define  SEV_CMD_INIT 146 
#define  SEV_CMD_LAUNCH_FINISH 145 
#define  SEV_CMD_LAUNCH_MEASURE 144 
#define  SEV_CMD_LAUNCH_START 143 
#define  SEV_CMD_LAUNCH_UPDATE_DATA 142 
#define  SEV_CMD_LAUNCH_UPDATE_SECRET 141 
#define  SEV_CMD_LAUNCH_UPDATE_VMSA 140 
#define  SEV_CMD_PDH_CERT_EXPORT 139 
#define  SEV_CMD_PEK_CERT_IMPORT 138 
#define  SEV_CMD_PEK_CSR 137 
#define  SEV_CMD_PLATFORM_STATUS 136 
#define  SEV_CMD_RECEIVE_FINISH 135 
#define  SEV_CMD_RECEIVE_START 134 
#define  SEV_CMD_RECEIVE_UPDATE_DATA 133 
#define  SEV_CMD_RECEIVE_UPDATE_VMSA 132 
#define  SEV_CMD_SEND_FINISH 131 
#define  SEV_CMD_SEND_START 130 
#define  SEV_CMD_SEND_UPDATE_DATA 129 
#define  SEV_CMD_SEND_UPDATE_VMSA 128 

__attribute__((used)) static int sev_cmd_buffer_len(int cmd)
{
	switch (cmd) {
	case SEV_CMD_INIT:			return sizeof(struct sev_data_init);
	case SEV_CMD_PLATFORM_STATUS:		return sizeof(struct sev_user_data_status);
	case SEV_CMD_PEK_CSR:			return sizeof(struct sev_data_pek_csr);
	case SEV_CMD_PEK_CERT_IMPORT:		return sizeof(struct sev_data_pek_cert_import);
	case SEV_CMD_PDH_CERT_EXPORT:		return sizeof(struct sev_data_pdh_cert_export);
	case SEV_CMD_LAUNCH_START:		return sizeof(struct sev_data_launch_start);
	case SEV_CMD_LAUNCH_UPDATE_DATA:	return sizeof(struct sev_data_launch_update_data);
	case SEV_CMD_LAUNCH_UPDATE_VMSA:	return sizeof(struct sev_data_launch_update_vmsa);
	case SEV_CMD_LAUNCH_FINISH:		return sizeof(struct sev_data_launch_finish);
	case SEV_CMD_LAUNCH_MEASURE:		return sizeof(struct sev_data_launch_measure);
	case SEV_CMD_ACTIVATE:			return sizeof(struct sev_data_activate);
	case SEV_CMD_DEACTIVATE:		return sizeof(struct sev_data_deactivate);
	case SEV_CMD_DECOMMISSION:		return sizeof(struct sev_data_decommission);
	case SEV_CMD_GUEST_STATUS:		return sizeof(struct sev_data_guest_status);
	case SEV_CMD_DBG_DECRYPT:		return sizeof(struct sev_data_dbg);
	case SEV_CMD_DBG_ENCRYPT:		return sizeof(struct sev_data_dbg);
	case SEV_CMD_SEND_START:		return sizeof(struct sev_data_send_start);
	case SEV_CMD_SEND_UPDATE_DATA:		return sizeof(struct sev_data_send_update_data);
	case SEV_CMD_SEND_UPDATE_VMSA:		return sizeof(struct sev_data_send_update_vmsa);
	case SEV_CMD_SEND_FINISH:		return sizeof(struct sev_data_send_finish);
	case SEV_CMD_RECEIVE_START:		return sizeof(struct sev_data_receive_start);
	case SEV_CMD_RECEIVE_FINISH:		return sizeof(struct sev_data_receive_finish);
	case SEV_CMD_RECEIVE_UPDATE_DATA:	return sizeof(struct sev_data_receive_update_data);
	case SEV_CMD_RECEIVE_UPDATE_VMSA:	return sizeof(struct sev_data_receive_update_vmsa);
	case SEV_CMD_LAUNCH_UPDATE_SECRET:	return sizeof(struct sev_data_launch_secret);
	case SEV_CMD_DOWNLOAD_FIRMWARE:		return sizeof(struct sev_data_download_firmware);
	case SEV_CMD_GET_ID:			return sizeof(struct sev_data_get_id);
	default:				return 0;
	}

	return 0;
}