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
struct target_core_fabric_ops {int dummy; } ;
struct se_session {int dummy; } ;
struct se_cmd {int data_direction; int sam_task_attr; unsigned char* sense_buffer; int state_active; int /*<<< orphan*/  data_length; struct se_session* se_sess; struct target_core_fabric_ops const* se_tfo; int /*<<< orphan*/  cmd_kref; int /*<<< orphan*/  work; int /*<<< orphan*/  t_state_lock; int /*<<< orphan*/ * abrt_compl; int /*<<< orphan*/ * free_compl; int /*<<< orphan*/  t_transport_stop_comp; int /*<<< orphan*/  state_list; int /*<<< orphan*/  se_cmd_list; int /*<<< orphan*/  se_qf_node; int /*<<< orphan*/  se_delayed_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void transport_init_se_cmd(
	struct se_cmd *cmd,
	const struct target_core_fabric_ops *tfo,
	struct se_session *se_sess,
	u32 data_length,
	int data_direction,
	int task_attr,
	unsigned char *sense_buffer)
{
	INIT_LIST_HEAD(&cmd->se_delayed_node);
	INIT_LIST_HEAD(&cmd->se_qf_node);
	INIT_LIST_HEAD(&cmd->se_cmd_list);
	INIT_LIST_HEAD(&cmd->state_list);
	init_completion(&cmd->t_transport_stop_comp);
	cmd->free_compl = NULL;
	cmd->abrt_compl = NULL;
	spin_lock_init(&cmd->t_state_lock);
	INIT_WORK(&cmd->work, NULL);
	kref_init(&cmd->cmd_kref);

	cmd->se_tfo = tfo;
	cmd->se_sess = se_sess;
	cmd->data_length = data_length;
	cmd->data_direction = data_direction;
	cmd->sam_task_attr = task_attr;
	cmd->sense_buffer = sense_buffer;

	cmd->state_active = false;
}