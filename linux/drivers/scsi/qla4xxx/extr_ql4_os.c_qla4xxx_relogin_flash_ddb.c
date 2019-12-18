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
struct scsi_qla_host {int /*<<< orphan*/  host_no; } ;
struct iscsi_session {struct ddb_entry* dd_data; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;
struct ddb_entry {int /*<<< orphan*/  fw_ddb_index; int /*<<< orphan*/  relogin_timer; int /*<<< orphan*/  default_relogin_timeout; struct scsi_qla_host* ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 scalar_t__ RELOGIN_TOV ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla4xxx_login_flash_ddb (struct iscsi_cls_session*) ; 

__attribute__((used)) static void qla4xxx_relogin_flash_ddb(struct iscsi_cls_session *cls_sess)
{
	uint16_t relogin_timer;
	struct iscsi_session *sess;
	struct ddb_entry *ddb_entry;
	struct scsi_qla_host *ha;

	sess = cls_sess->dd_data;
	ddb_entry = sess->dd_data;
	ha = ddb_entry->ha;

	relogin_timer = max(ddb_entry->default_relogin_timeout,
			    (uint16_t)RELOGIN_TOV);
	atomic_set(&ddb_entry->relogin_timer, relogin_timer);

	DEBUG2(ql4_printk(KERN_INFO, ha,
			  "scsi%ld: Relogin index [%d]. TOV=%d\n", ha->host_no,
			  ddb_entry->fw_ddb_index, relogin_timer));

	qla4xxx_login_flash_ddb(cls_sess);
}