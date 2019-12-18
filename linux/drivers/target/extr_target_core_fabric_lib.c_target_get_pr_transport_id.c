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
struct t10_pr_registration {int dummy; } ;
struct se_node_acl {TYPE_1__* se_tpg; } ;
struct TYPE_2__ {int proto_id; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SCSI_PROTOCOL_FCP 132 
#define  SCSI_PROTOCOL_ISCSI 131 
#define  SCSI_PROTOCOL_SAS 130 
#define  SCSI_PROTOCOL_SBP 129 
#define  SCSI_PROTOCOL_SRP 128 
 int fc_get_pr_transport_id (struct se_node_acl*,int*,unsigned char*) ; 
 int iscsi_get_pr_transport_id (struct se_node_acl*,struct t10_pr_registration*,int*,unsigned char*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int sas_get_pr_transport_id (struct se_node_acl*,int*,unsigned char*) ; 
 int sbp_get_pr_transport_id (struct se_node_acl*,int*,unsigned char*) ; 
 int srp_get_pr_transport_id (struct se_node_acl*,int*,unsigned char*) ; 

int target_get_pr_transport_id(struct se_node_acl *nacl,
		struct t10_pr_registration *pr_reg, int *format_code,
		unsigned char *buf)
{
	switch (nacl->se_tpg->proto_id) {
	case SCSI_PROTOCOL_SAS:
		return sas_get_pr_transport_id(nacl, format_code, buf);
	case SCSI_PROTOCOL_SBP:
		return sbp_get_pr_transport_id(nacl, format_code, buf);
	case SCSI_PROTOCOL_SRP:
		return srp_get_pr_transport_id(nacl, format_code, buf);
	case SCSI_PROTOCOL_FCP:
		return fc_get_pr_transport_id(nacl, format_code, buf);
	case SCSI_PROTOCOL_ISCSI:
		return iscsi_get_pr_transport_id(nacl, pr_reg, format_code,
				buf);
	default:
		pr_err("Unknown proto_id: 0x%02x\n", nacl->se_tpg->proto_id);
		return -EINVAL;
	}
}