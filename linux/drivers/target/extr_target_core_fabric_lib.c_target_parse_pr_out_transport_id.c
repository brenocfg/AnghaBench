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
struct se_portal_group {int proto_id; } ;

/* Variables and functions */
#define  SCSI_PROTOCOL_FCP 132 
#define  SCSI_PROTOCOL_ISCSI 131 
#define  SCSI_PROTOCOL_SAS 130 
#define  SCSI_PROTOCOL_SBP 129 
#define  SCSI_PROTOCOL_SRP 128 
 char const* iscsi_parse_pr_out_transport_id (struct se_portal_group*,char*,int*,char**) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

const char *target_parse_pr_out_transport_id(struct se_portal_group *tpg,
		char *buf, u32 *out_tid_len, char **port_nexus_ptr)
{
	u32 offset;

	switch (tpg->proto_id) {
	case SCSI_PROTOCOL_SAS:
		/*
		 * Assume the FORMAT CODE 00b from spc4r17, 7.5.4.7 TransportID
		 * for initiator ports using SCSI over SAS Serial SCSI Protocol.
		 */
		offset = 4;
		break;
	case SCSI_PROTOCOL_SBP:
	case SCSI_PROTOCOL_SRP:
	case SCSI_PROTOCOL_FCP:
		offset = 8;
		break;
	case SCSI_PROTOCOL_ISCSI:
		return iscsi_parse_pr_out_transport_id(tpg, buf, out_tid_len,
					port_nexus_ptr);
	default:
		pr_err("Unknown proto_id: 0x%02x\n", tpg->proto_id);
		return NULL;
	}

	*port_nexus_ptr = NULL;
	*out_tid_len = 24;
	return buf + offset;
}