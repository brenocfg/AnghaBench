#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct se_session {scalar_t__ sess_cmd_map; int /*<<< orphan*/  sess_tag_pool; } ;
struct iscsi_conn {TYPE_2__* conn_transport; TYPE_1__* sess; } ;
struct TYPE_6__ {int map_tag; int map_cpu; } ;
struct iscsi_cmd {int /*<<< orphan*/  dataout_timer; int /*<<< orphan*/  r2t_lock; int /*<<< orphan*/  error_lock; int /*<<< orphan*/  istate_lock; int /*<<< orphan*/  dataout_timeout_lock; int /*<<< orphan*/  datain_lock; int /*<<< orphan*/  cmd_r2t_list; int /*<<< orphan*/  datain_list; int /*<<< orphan*/  i_conn_node; int /*<<< orphan*/  data_direction; struct iscsi_conn* conn; TYPE_3__ se_cmd; } ;
struct TYPE_5__ {int priv_size; } ;
struct TYPE_4__ {struct se_session* se_sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsit_handle_dataout_timeout ; 
 int iscsit_wait_for_tag (struct se_session*,int,int*) ; 
 int /*<<< orphan*/  memset (struct iscsi_cmd*,int /*<<< orphan*/ ,int) ; 
 int sbitmap_queue_get (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct iscsi_cmd *iscsit_allocate_cmd(struct iscsi_conn *conn, int state)
{
	struct iscsi_cmd *cmd;
	struct se_session *se_sess = conn->sess->se_sess;
	int size, tag, cpu;

	tag = sbitmap_queue_get(&se_sess->sess_tag_pool, &cpu);
	if (tag < 0)
		tag = iscsit_wait_for_tag(se_sess, state, &cpu);
	if (tag < 0)
		return NULL;

	size = sizeof(struct iscsi_cmd) + conn->conn_transport->priv_size;
	cmd = (struct iscsi_cmd *)(se_sess->sess_cmd_map + (tag * size));
	memset(cmd, 0, size);

	cmd->se_cmd.map_tag = tag;
	cmd->se_cmd.map_cpu = cpu;
	cmd->conn = conn;
	cmd->data_direction = DMA_NONE;
	INIT_LIST_HEAD(&cmd->i_conn_node);
	INIT_LIST_HEAD(&cmd->datain_list);
	INIT_LIST_HEAD(&cmd->cmd_r2t_list);
	spin_lock_init(&cmd->datain_lock);
	spin_lock_init(&cmd->dataout_timeout_lock);
	spin_lock_init(&cmd->istate_lock);
	spin_lock_init(&cmd->error_lock);
	spin_lock_init(&cmd->r2t_lock);
	timer_setup(&cmd->dataout_timer, iscsit_handle_dataout_timeout, 0);

	return cmd;
}