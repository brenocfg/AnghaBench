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
typedef  scalar_t__ uint16_t ;
struct iscsi_session {struct ddb_entry* dd_data; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;
struct device {int dummy; } ;
struct ddb_entry {scalar_t__ chap_tbl_idx; } ;

/* Variables and functions */
 struct iscsi_cls_session* iscsi_dev_to_session (struct device*) ; 
 int /*<<< orphan*/  iscsi_is_session_dev (struct device*) ; 
 scalar_t__ iscsi_session_chkready (struct iscsi_cls_session*) ; 

__attribute__((used)) static int __qla4xxx_is_chap_active(struct device *dev, void *data)
{
	int ret = 0;
	uint16_t *chap_tbl_idx = (uint16_t *) data;
	struct iscsi_cls_session *cls_session;
	struct iscsi_session *sess;
	struct ddb_entry *ddb_entry;

	if (!iscsi_is_session_dev(dev))
		goto exit_is_chap_active;

	cls_session = iscsi_dev_to_session(dev);
	sess = cls_session->dd_data;
	ddb_entry = sess->dd_data;

	if (iscsi_session_chkready(cls_session))
		goto exit_is_chap_active;

	if (ddb_entry->chap_tbl_idx == *chap_tbl_idx)
		ret = 1;

exit_is_chap_active:
	return ret;
}