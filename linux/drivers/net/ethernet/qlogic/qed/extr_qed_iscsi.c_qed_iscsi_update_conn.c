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
typedef  int /*<<< orphan*/  u32 ;
struct qed_iscsi_params_update {int /*<<< orphan*/  exp_stat_sn; int /*<<< orphan*/  first_seq_length; int /*<<< orphan*/  max_send_pdu_length; int /*<<< orphan*/  max_recv_pdu_length; int /*<<< orphan*/  max_seq_size; int /*<<< orphan*/  update_flag; } ;
struct qed_iscsi_conn {int /*<<< orphan*/  exp_stat_sn; int /*<<< orphan*/  first_seq_length; int /*<<< orphan*/  max_send_pdu_length; int /*<<< orphan*/  max_recv_pdu_length; int /*<<< orphan*/  max_seq_size; int /*<<< orphan*/  update_flag; } ;
struct qed_hash_iscsi_con {struct qed_iscsi_conn* con; } ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_dev*,char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  QED_AFFIN_HWFN (struct qed_dev*) ; 
 int /*<<< orphan*/  QED_SPQ_MODE_EBLOCK ; 
 struct qed_hash_iscsi_con* qed_iscsi_get_hash (struct qed_dev*,int /*<<< orphan*/ ) ; 
 int qed_sp_iscsi_conn_update (int /*<<< orphan*/ ,struct qed_iscsi_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_iscsi_update_conn(struct qed_dev *cdev,
				 u32 handle,
				 struct qed_iscsi_params_update *conn_info)
{
	struct qed_hash_iscsi_con *hash_con;
	struct qed_iscsi_conn *con;

	hash_con = qed_iscsi_get_hash(cdev, handle);
	if (!hash_con) {
		DP_NOTICE(cdev, "Failed to find connection for handle %d\n",
			  handle);
		return -EINVAL;
	}

	/* Update the connection with information from the params */
	con = hash_con->con;
	con->update_flag = conn_info->update_flag;
	con->max_seq_size = conn_info->max_seq_size;
	con->max_recv_pdu_length = conn_info->max_recv_pdu_length;
	con->max_send_pdu_length = conn_info->max_send_pdu_length;
	con->first_seq_length = conn_info->first_seq_length;
	con->exp_stat_sn = conn_info->exp_stat_sn;

	return qed_sp_iscsi_conn_update(QED_AFFIN_HWFN(cdev), con,
					QED_SPQ_MODE_EBLOCK, NULL);
}