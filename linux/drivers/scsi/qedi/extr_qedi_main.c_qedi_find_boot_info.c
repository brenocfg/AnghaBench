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
typedef  int u32 ;
struct qedi_ctx {int max_active_conns; } ;
struct qedi_conn {struct iscsi_cls_conn* cls_conn; TYPE_2__* ep; } ;
struct qedi_boot_target {int /*<<< orphan*/  ip_addr; int /*<<< orphan*/  iscsi_name; } ;
struct qed_mfw_tlv_iscsi {int header_digest_set; int header_digest; int data_digest_set; int data_digest; int boot_taget_portal_set; int /*<<< orphan*/  boot_taget_portal; } ;
struct nvm_iscsi_block {TYPE_1__* target; } ;
struct iscsi_session {char* targetname; int /*<<< orphan*/  tpgt; } ;
struct iscsi_conn {scalar_t__ datadgst_en; scalar_t__ hdrdgst_en; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct TYPE_4__ {scalar_t__ ip_type; int /*<<< orphan*/  dst_addr; } ;
struct TYPE_3__ {int ctrl_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPV4_LEN ; 
 int /*<<< orphan*/  IPV6_LEN ; 
 int NVM_ISCSI_CFG_TARGET_ENABLED ; 
 scalar_t__ TCP_IPV4 ; 
 struct iscsi_cls_session* iscsi_conn_to_session (struct iscsi_cls_conn*) ; 
 int /*<<< orphan*/  iscsi_is_session_online (struct iscsi_cls_session*) ; 
 int /*<<< orphan*/  kfree (struct qedi_boot_target*) ; 
 struct qedi_boot_target* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedi_get_boot_tgt_info (struct nvm_iscsi_block*,struct qedi_boot_target*,int) ; 
 struct qedi_conn* qedi_get_conn_from_id (struct qedi_ctx*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int qedi_find_boot_info(struct qedi_ctx *qedi,
			       struct qed_mfw_tlv_iscsi *iscsi,
			       struct nvm_iscsi_block *block)
{
	struct qedi_boot_target *pri_tgt = NULL, *sec_tgt = NULL;
	u32 pri_ctrl_flags = 0, sec_ctrl_flags = 0, found = 0;
	struct iscsi_cls_session *cls_sess;
	struct iscsi_cls_conn *cls_conn;
	struct qedi_conn *qedi_conn;
	struct iscsi_session *sess;
	struct iscsi_conn *conn;
	char ep_ip_addr[64];
	int i, ret = 0;

	pri_ctrl_flags = !!(block->target[0].ctrl_flags &
					NVM_ISCSI_CFG_TARGET_ENABLED);
	if (pri_ctrl_flags) {
		pri_tgt = kzalloc(sizeof(*pri_tgt), GFP_KERNEL);
		if (!pri_tgt)
			return -1;
		qedi_get_boot_tgt_info(block, pri_tgt, 0);
	}

	sec_ctrl_flags = !!(block->target[1].ctrl_flags &
					NVM_ISCSI_CFG_TARGET_ENABLED);
	if (sec_ctrl_flags) {
		sec_tgt = kzalloc(sizeof(*sec_tgt), GFP_KERNEL);
		if (!sec_tgt) {
			ret = -1;
			goto free_tgt;
		}
		qedi_get_boot_tgt_info(block, sec_tgt, 1);
	}

	for (i = 0; i < qedi->max_active_conns; i++) {
		qedi_conn = qedi_get_conn_from_id(qedi, i);
		if (!qedi_conn)
			continue;

		if (qedi_conn->ep->ip_type == TCP_IPV4)
			snprintf(ep_ip_addr, IPV4_LEN, "%pI4\n",
				 qedi_conn->ep->dst_addr);
		else
			snprintf(ep_ip_addr, IPV6_LEN, "%pI6\n",
				 qedi_conn->ep->dst_addr);

		cls_conn = qedi_conn->cls_conn;
		conn = cls_conn->dd_data;
		cls_sess = iscsi_conn_to_session(cls_conn);
		sess = cls_sess->dd_data;

		if (!iscsi_is_session_online(cls_sess))
			continue;

		if (!sess->targetname)
			continue;

		if (pri_ctrl_flags) {
			if (!strcmp(pri_tgt->iscsi_name, sess->targetname) &&
			    !strcmp(pri_tgt->ip_addr, ep_ip_addr)) {
				found = 1;
				break;
			}
		}

		if (sec_ctrl_flags) {
			if (!strcmp(sec_tgt->iscsi_name, sess->targetname) &&
			    !strcmp(sec_tgt->ip_addr, ep_ip_addr)) {
				found = 1;
				break;
			}
		}
	}

	if (found) {
		if (conn->hdrdgst_en) {
			iscsi->header_digest_set = true;
			iscsi->header_digest = 1;
		}

		if (conn->datadgst_en) {
			iscsi->data_digest_set = true;
			iscsi->data_digest = 1;
		}
		iscsi->boot_taget_portal_set = true;
		iscsi->boot_taget_portal = sess->tpgt;

	} else {
		ret = -1;
	}

	if (sec_ctrl_flags)
		kfree(sec_tgt);
free_tgt:
	if (pri_ctrl_flags)
		kfree(pri_tgt);

	return ret;
}