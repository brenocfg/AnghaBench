#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct mlx5_cmd {struct mlx5_cmd_stats* stats; int /*<<< orphan*/  wq; } ;
struct mlx5_core_dev {struct mlx5_cmd cmd; } ;
struct mlx5_cmd_work_ent {int polling; int /*<<< orphan*/  status; scalar_t__ ts1; scalar_t__ ts2; int /*<<< orphan*/  work; int /*<<< orphan*/  cb_timeout_work; int /*<<< orphan*/  done; int /*<<< orphan*/  token; } ;
struct mlx5_cmd_stats {int /*<<< orphan*/  lock; int /*<<< orphan*/  n; int /*<<< orphan*/  sum; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct mlx5_cmd_msg {TYPE_1__ first; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  mlx5_cmd_cbk_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct mlx5_cmd_stats*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 scalar_t__ IS_ERR (struct mlx5_cmd_work_ent*) ; 
 int MLX5_CMD_TIME ; 
 size_t MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct mlx5_cmd_work_ent*) ; 
 struct mlx5_cmd_work_ent* alloc_cmd (struct mlx5_cmd*,struct mlx5_cmd_msg*,struct mlx5_cmd_msg*,void*,int,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  cb_timeout_handler ; 
 int /*<<< orphan*/  cmd_work_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_cmd (struct mlx5_cmd_work_ent*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbox_in ; 
 int /*<<< orphan*/  mlx5_command_str (size_t) ; 
 int /*<<< orphan*/  mlx5_core_dbg_mask (struct mlx5_core_dev*,int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  opcode ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int wait_func (struct mlx5_core_dev*,struct mlx5_cmd_work_ent*) ; 

__attribute__((used)) static int mlx5_cmd_invoke(struct mlx5_core_dev *dev, struct mlx5_cmd_msg *in,
			   struct mlx5_cmd_msg *out, void *uout, int uout_size,
			   mlx5_cmd_cbk_t callback,
			   void *context, int page_queue, u8 *status,
			   u8 token, bool force_polling)
{
	struct mlx5_cmd *cmd = &dev->cmd;
	struct mlx5_cmd_work_ent *ent;
	struct mlx5_cmd_stats *stats;
	int err = 0;
	s64 ds;
	u16 op;

	if (callback && page_queue)
		return -EINVAL;

	ent = alloc_cmd(cmd, in, out, uout, uout_size, callback, context,
			page_queue);
	if (IS_ERR(ent))
		return PTR_ERR(ent);

	ent->token = token;
	ent->polling = force_polling;

	if (!callback)
		init_completion(&ent->done);

	INIT_DELAYED_WORK(&ent->cb_timeout_work, cb_timeout_handler);
	INIT_WORK(&ent->work, cmd_work_handler);
	if (page_queue) {
		cmd_work_handler(&ent->work);
	} else if (!queue_work(cmd->wq, &ent->work)) {
		mlx5_core_warn(dev, "failed to queue work\n");
		err = -ENOMEM;
		goto out_free;
	}

	if (callback)
		goto out;

	err = wait_func(dev, ent);
	if (err == -ETIMEDOUT)
		goto out;

	ds = ent->ts2 - ent->ts1;
	op = MLX5_GET(mbox_in, in->first.data, opcode);
	if (op < ARRAY_SIZE(cmd->stats)) {
		stats = &cmd->stats[op];
		spin_lock_irq(&stats->lock);
		stats->sum += ds;
		++stats->n;
		spin_unlock_irq(&stats->lock);
	}
	mlx5_core_dbg_mask(dev, 1 << MLX5_CMD_TIME,
			   "fw exec time for %s is %lld nsec\n",
			   mlx5_command_str(op), ds);
	*status = ent->status;

out_free:
	free_cmd(ent);
out:
	return err;
}