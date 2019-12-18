#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct semaphore {int dummy; } ;
struct mlx5_cmd {int log_sz; struct mlx5_cmd_stats* stats; int /*<<< orphan*/  checksum_disabled; struct semaphore sem; struct semaphore pages_sem; struct mlx5_cmd_work_ent** ent_arr; } ;
struct mlx5_core_dev {struct mlx5_cmd cmd; } ;
struct mlx5_cmd_work_ent {int ret; int status; size_t op; int /*<<< orphan*/  done; TYPE_6__* in; TYPE_4__* out; int /*<<< orphan*/  uout; int /*<<< orphan*/  uout_size; void* context; int /*<<< orphan*/  (* callback ) (int,void*) ;scalar_t__ ts1; scalar_t__ ts2; int /*<<< orphan*/  idx; TYPE_2__* lay; scalar_t__ page_queue; int /*<<< orphan*/  cb_timeout_work; int /*<<< orphan*/  state; } ;
struct mlx5_cmd_stats {int /*<<< orphan*/  lock; int /*<<< orphan*/  n; int /*<<< orphan*/  sum; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  (* mlx5_cmd_cbk_t ) (int,void*) ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_3__ first; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_1__ first; } ;
struct TYPE_8__ {int status_own; int /*<<< orphan*/  out; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct mlx5_cmd_stats*) ; 
 int /*<<< orphan*/  MLX5_CMD_ENT_STATE_PENDING_COMP ; 
 int MLX5_DRIVER_STATUS_ABORTED ; 
 int MLX5_TRIGGERED_CMD_COMP ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deliv_status_to_str (int) ; 
 int /*<<< orphan*/  dump_command (struct mlx5_core_dev*,struct mlx5_cmd_work_ent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cmd (struct mlx5_cmd_work_ent*) ; 
 int /*<<< orphan*/  free_ent (struct mlx5_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_msg (struct mlx5_core_dev*,TYPE_6__*) ; 
 scalar_t__ ktime_get_ns () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mlx5_cmd_check (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5_copy_from_msg (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_free_cmd_msg (struct mlx5_core_dev*,TYPE_4__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  up (struct semaphore*) ; 
 int verify_signature (struct mlx5_cmd_work_ent*) ; 

__attribute__((used)) static void mlx5_cmd_comp_handler(struct mlx5_core_dev *dev, u64 vec, bool forced)
{
	struct mlx5_cmd *cmd = &dev->cmd;
	struct mlx5_cmd_work_ent *ent;
	mlx5_cmd_cbk_t callback;
	void *context;
	int err;
	int i;
	s64 ds;
	struct mlx5_cmd_stats *stats;
	unsigned long flags;
	unsigned long vector;

	/* there can be at most 32 command queues */
	vector = vec & 0xffffffff;
	for (i = 0; i < (1 << cmd->log_sz); i++) {
		if (test_bit(i, &vector)) {
			struct semaphore *sem;

			ent = cmd->ent_arr[i];

			/* if we already completed the command, ignore it */
			if (!test_and_clear_bit(MLX5_CMD_ENT_STATE_PENDING_COMP,
						&ent->state)) {
				/* only real completion can free the cmd slot */
				if (!forced) {
					mlx5_core_err(dev, "Command completion arrived after timeout (entry idx = %d).\n",
						      ent->idx);
					free_ent(cmd, ent->idx);
					free_cmd(ent);
				}
				continue;
			}

			if (ent->callback)
				cancel_delayed_work(&ent->cb_timeout_work);
			if (ent->page_queue)
				sem = &cmd->pages_sem;
			else
				sem = &cmd->sem;
			ent->ts2 = ktime_get_ns();
			memcpy(ent->out->first.data, ent->lay->out, sizeof(ent->lay->out));
			dump_command(dev, ent, 0);
			if (!ent->ret) {
				if (!cmd->checksum_disabled)
					ent->ret = verify_signature(ent);
				else
					ent->ret = 0;
				if (vec & MLX5_TRIGGERED_CMD_COMP)
					ent->status = MLX5_DRIVER_STATUS_ABORTED;
				else
					ent->status = ent->lay->status_own >> 1;

				mlx5_core_dbg(dev, "command completed. ret 0x%x, delivery status %s(0x%x)\n",
					      ent->ret, deliv_status_to_str(ent->status), ent->status);
			}

			/* only real completion will free the entry slot */
			if (!forced)
				free_ent(cmd, ent->idx);

			if (ent->callback) {
				ds = ent->ts2 - ent->ts1;
				if (ent->op < ARRAY_SIZE(cmd->stats)) {
					stats = &cmd->stats[ent->op];
					spin_lock_irqsave(&stats->lock, flags);
					stats->sum += ds;
					++stats->n;
					spin_unlock_irqrestore(&stats->lock, flags);
				}

				callback = ent->callback;
				context = ent->context;
				err = ent->ret;
				if (!err) {
					err = mlx5_copy_from_msg(ent->uout,
								 ent->out,
								 ent->uout_size);

					err = err ? err : mlx5_cmd_check(dev,
									ent->in->first.data,
									ent->uout);
				}

				mlx5_free_cmd_msg(dev, ent->out);
				free_msg(dev, ent->in);

				err = err ? err : ent->status;
				if (!forced)
					free_cmd(ent);
				callback(err, context);
			} else {
				complete(&ent->done);
			}
			up(sem);
		}
	}
}