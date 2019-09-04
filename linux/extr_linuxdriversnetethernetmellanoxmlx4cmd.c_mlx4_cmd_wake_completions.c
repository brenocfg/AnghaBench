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
struct TYPE_2__ {int max_cmds; int /*<<< orphan*/  context_lock; struct mlx4_cmd_context* context; } ;
struct mlx4_priv {TYPE_1__ cmd; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_context {int /*<<< orphan*/  done; int /*<<< orphan*/  result; int /*<<< orphan*/  fw_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_STAT_INTERNAL_ERR ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_status_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void mlx4_cmd_wake_completions(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_cmd_context *context;
	int i;

	spin_lock(&priv->cmd.context_lock);
	if (priv->cmd.context) {
		for (i = 0; i < priv->cmd.max_cmds; ++i) {
			context = &priv->cmd.context[i];
			context->fw_status = CMD_STAT_INTERNAL_ERR;
			context->result    =
				mlx4_status_to_errno(CMD_STAT_INTERNAL_ERR);
			complete(&context->done);
		}
	}
	spin_unlock(&priv->cmd.context_lock);
}