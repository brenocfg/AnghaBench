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
struct TYPE_2__ {int max_cmds; int /*<<< orphan*/  slave_cmd_mutex; int /*<<< orphan*/  switch_sem; int /*<<< orphan*/  poll_sem; int /*<<< orphan*/ * context; int /*<<< orphan*/  event_sem; scalar_t__ use_events; } ;
struct mlx4_priv {TYPE_1__ cmd; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ mlx4_is_mfunc (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void mlx4_cmd_use_polling(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int i;

	if (mlx4_is_mfunc(dev))
		mutex_lock(&priv->cmd.slave_cmd_mutex);
	down_write(&priv->cmd.switch_sem);
	priv->cmd.use_events = 0;

	for (i = 0; i < priv->cmd.max_cmds; ++i)
		down(&priv->cmd.event_sem);

	kfree(priv->cmd.context);
	priv->cmd.context = NULL;

	up(&priv->cmd.poll_sem);
	up_write(&priv->cmd.switch_sem);
	if (mlx4_is_mfunc(dev))
		mutex_unlock(&priv->cmd.slave_cmd_mutex);
}