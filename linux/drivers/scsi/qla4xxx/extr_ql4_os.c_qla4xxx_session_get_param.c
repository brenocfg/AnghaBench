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
typedef  int /*<<< orphan*/  uint16_t ;
struct scsi_qla_host {int dummy; } ;
struct ql4_chap_table {int /*<<< orphan*/  secret_len; scalar_t__ secret; scalar_t__ name; } ;
struct iscsi_session {int /*<<< orphan*/  password; int /*<<< orphan*/  username; int /*<<< orphan*/  password_in; int /*<<< orphan*/  username_in; struct ddb_entry* dd_data; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;
struct iscsi_cls_conn {int dummy; } ;
struct ddb_entry {int /*<<< orphan*/  chap_tbl_idx; int /*<<< orphan*/  ddb_type; struct iscsi_cls_conn* conn; struct scsi_qla_host* ha; } ;
typedef  enum iscsi_param { ____Placeholder_iscsi_param } iscsi_param ;
typedef  int /*<<< orphan*/  chap_tbl ;

/* Variables and functions */
 int /*<<< orphan*/  BIDI_CHAP ; 
 int /*<<< orphan*/  FLASH_DDB ; 
 int /*<<< orphan*/  INVALID_ENTRY ; 
#define  ISCSI_PARAM_CHAP_IN_IDX 131 
#define  ISCSI_PARAM_CHAP_OUT_IDX 130 
#define  ISCSI_PARAM_PASSWORD 129 
#define  ISCSI_PARAM_USERNAME 128 
 int /*<<< orphan*/  LOCAL_CHAP ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 int iscsi_session_get_param (struct iscsi_cls_session*,int,char*) ; 
 int /*<<< orphan*/  iscsi_set_param (struct iscsi_cls_conn*,int const,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ql4_chap_table*,int /*<<< orphan*/ ,int) ; 
 int qla4xxx_get_chap_index (struct scsi_qla_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int qla4xxx_get_uni_chap_at_index (struct scsi_qla_host*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int qla4xxx_session_get_param(struct iscsi_cls_session *cls_sess,
				     enum iscsi_param param, char *buf)
{
	struct iscsi_session *sess = cls_sess->dd_data;
	struct ddb_entry *ddb_entry = sess->dd_data;
	struct scsi_qla_host *ha = ddb_entry->ha;
	struct iscsi_cls_conn *cls_conn = ddb_entry->conn;
	struct ql4_chap_table chap_tbl;
	int rval, len;
	uint16_t idx;

	memset(&chap_tbl, 0, sizeof(chap_tbl));
	switch (param) {
	case ISCSI_PARAM_CHAP_IN_IDX:
		rval = qla4xxx_get_chap_index(ha, sess->username_in,
					      sess->password_in, BIDI_CHAP,
					      &idx);
		if (rval)
			len = sprintf(buf, "\n");
		else
			len = sprintf(buf, "%hu\n", idx);
		break;
	case ISCSI_PARAM_CHAP_OUT_IDX:
		if (ddb_entry->ddb_type == FLASH_DDB) {
			if (ddb_entry->chap_tbl_idx != INVALID_ENTRY) {
				idx = ddb_entry->chap_tbl_idx;
				rval = QLA_SUCCESS;
			} else {
				rval = QLA_ERROR;
			}
		} else {
			rval = qla4xxx_get_chap_index(ha, sess->username,
						      sess->password,
						      LOCAL_CHAP, &idx);
		}
		if (rval)
			len = sprintf(buf, "\n");
		else
			len = sprintf(buf, "%hu\n", idx);
		break;
	case ISCSI_PARAM_USERNAME:
	case ISCSI_PARAM_PASSWORD:
		/* First, populate session username and password for FLASH DDB,
		 * if not already done. This happens when session login fails
		 * for a FLASH DDB.
		 */
		if (ddb_entry->ddb_type == FLASH_DDB &&
		    ddb_entry->chap_tbl_idx != INVALID_ENTRY &&
		    !sess->username && !sess->password) {
			idx = ddb_entry->chap_tbl_idx;
			rval = qla4xxx_get_uni_chap_at_index(ha, chap_tbl.name,
							    chap_tbl.secret,
							    idx);
			if (!rval) {
				iscsi_set_param(cls_conn, ISCSI_PARAM_USERNAME,
						(char *)chap_tbl.name,
						strlen((char *)chap_tbl.name));
				iscsi_set_param(cls_conn, ISCSI_PARAM_PASSWORD,
						(char *)chap_tbl.secret,
						chap_tbl.secret_len);
			}
		}
		/* fall through */
	default:
		return iscsi_session_get_param(cls_sess, param, buf);
	}

	return len;
}