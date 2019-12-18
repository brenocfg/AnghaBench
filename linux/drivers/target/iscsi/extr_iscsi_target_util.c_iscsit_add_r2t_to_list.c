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
typedef  void* u32 ;
struct iscsi_r2t {int recovery_r2t; int /*<<< orphan*/  r2t_list; void* xfer_len; void* offset; void* r2t_sn; } ;
struct iscsi_cmd {int /*<<< orphan*/  r2t_lock; int /*<<< orphan*/  conn; int /*<<< orphan*/  cmd_r2t_list; int /*<<< orphan*/  r2t_sn; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISTATE_SEND_R2T ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  iscsit_add_cmd_to_immediate_queue (struct iscsi_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iscsi_r2t* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_r2t_cache ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int iscsit_add_r2t_to_list(
	struct iscsi_cmd *cmd,
	u32 offset,
	u32 xfer_len,
	int recovery,
	u32 r2t_sn)
{
	struct iscsi_r2t *r2t;

	lockdep_assert_held(&cmd->r2t_lock);

	WARN_ON_ONCE((s32)xfer_len < 0);

	r2t = kmem_cache_zalloc(lio_r2t_cache, GFP_ATOMIC);
	if (!r2t) {
		pr_err("Unable to allocate memory for struct iscsi_r2t.\n");
		return -1;
	}
	INIT_LIST_HEAD(&r2t->r2t_list);

	r2t->recovery_r2t = recovery;
	r2t->r2t_sn = (!r2t_sn) ? cmd->r2t_sn++ : r2t_sn;
	r2t->offset = offset;
	r2t->xfer_len = xfer_len;
	list_add_tail(&r2t->r2t_list, &cmd->cmd_r2t_list);
	spin_unlock_bh(&cmd->r2t_lock);

	iscsit_add_cmd_to_immediate_queue(cmd, cmd->conn, ISTATE_SEND_R2T);

	spin_lock_bh(&cmd->r2t_lock);
	return 0;
}