#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_qla_host {int dummy; } ;
struct iscsi_session {int /*<<< orphan*/ * targetname; } ;
struct iscsi_conn {int /*<<< orphan*/  persistent_port; int /*<<< orphan*/ * persistent_address; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct ddb_entry {scalar_t__ ddb_type; TYPE_2__* conn; TYPE_1__* sess; } ;
struct TYPE_4__ {struct iscsi_conn* dd_data; } ;
struct TYPE_3__ {struct iscsi_session* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 (int /*<<< orphan*/ ) ; 
 scalar_t__ FLASH_DDB ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int MAX_DEV_DB_ENTRIES ; 
 int MAX_DEV_DB_ENTRIES_40XX ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 scalar_t__ is_qla40XX (struct scsi_qla_host*) ; 
 struct iscsi_cls_session* iscsi_conn_to_session (struct iscsi_cls_conn*) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*,...) ; 
 struct ddb_entry* qla4xxx_lookup_ddb_by_fw_index (struct scsi_qla_host*,int) ; 
 int qla4xxx_match_ipaddress (struct scsi_qla_host*,struct ddb_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qla4xxx_match_fwdb_session(struct scsi_qla_host *ha,
				      struct iscsi_cls_conn *cls_conn)
{
	int idx = 0, max_ddbs, rval;
	struct iscsi_cls_session *cls_sess = iscsi_conn_to_session(cls_conn);
	struct iscsi_session *sess, *existing_sess;
	struct iscsi_conn *conn, *existing_conn;
	struct ddb_entry *ddb_entry;

	sess = cls_sess->dd_data;
	conn = cls_conn->dd_data;

	if (sess->targetname == NULL ||
	    conn->persistent_address == NULL ||
	    conn->persistent_port == 0)
		return QLA_ERROR;

	max_ddbs =  is_qla40XX(ha) ? MAX_DEV_DB_ENTRIES_40XX :
				     MAX_DEV_DB_ENTRIES;

	for (idx = 0; idx < max_ddbs; idx++) {
		ddb_entry = qla4xxx_lookup_ddb_by_fw_index(ha, idx);
		if (ddb_entry == NULL)
			continue;

		if (ddb_entry->ddb_type != FLASH_DDB)
			continue;

		existing_sess = ddb_entry->sess->dd_data;
		existing_conn = ddb_entry->conn->dd_data;

		if (existing_sess->targetname == NULL ||
		    existing_conn->persistent_address == NULL ||
		    existing_conn->persistent_port == 0)
			continue;

		DEBUG2(ql4_printk(KERN_INFO, ha,
				  "IQN = %s User IQN = %s\n",
				  existing_sess->targetname,
				  sess->targetname));

		DEBUG2(ql4_printk(KERN_INFO, ha,
				  "IP = %s User IP = %s\n",
				  existing_conn->persistent_address,
				  conn->persistent_address));

		DEBUG2(ql4_printk(KERN_INFO, ha,
				  "Port = %d User Port = %d\n",
				  existing_conn->persistent_port,
				  conn->persistent_port));

		if (strcmp(existing_sess->targetname, sess->targetname))
			continue;
		rval = qla4xxx_match_ipaddress(ha, ddb_entry,
					existing_conn->persistent_address,
					conn->persistent_address);
		if (rval == QLA_ERROR)
			continue;
		if (existing_conn->persistent_port != conn->persistent_port)
			continue;
		break;
	}

	if (idx == max_ddbs)
		return QLA_ERROR;

	DEBUG2(ql4_printk(KERN_INFO, ha,
			  "Match found in fwdb sessions\n"));
	return QLA_SUCCESS;
}