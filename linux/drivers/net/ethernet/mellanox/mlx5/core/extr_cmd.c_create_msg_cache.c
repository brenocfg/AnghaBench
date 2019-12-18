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
struct mlx5_cmd {struct cmd_msg_cache* cache; } ;
struct mlx5_core_dev {struct mlx5_cmd cmd; } ;
struct mlx5_cmd_msg {int /*<<< orphan*/  list; struct cmd_msg_cache* parent; } ;
struct cmd_msg_cache {int num_ent; int /*<<< orphan*/  head; int /*<<< orphan*/  max_inbox_size; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct mlx5_cmd_msg*) ; 
 int MLX5_NUM_COMMAND_CACHES ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/ * cmd_cache_ent_size ; 
 int* cmd_cache_num_ent ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mlx5_cmd_msg* mlx5_alloc_cmd_msg (struct mlx5_core_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void create_msg_cache(struct mlx5_core_dev *dev)
{
	struct mlx5_cmd *cmd = &dev->cmd;
	struct cmd_msg_cache *ch;
	struct mlx5_cmd_msg *msg;
	int i;
	int k;

	/* Initialize and fill the caches with initial entries */
	for (k = 0; k < MLX5_NUM_COMMAND_CACHES; k++) {
		ch = &cmd->cache[k];
		spin_lock_init(&ch->lock);
		INIT_LIST_HEAD(&ch->head);
		ch->num_ent = cmd_cache_num_ent[k];
		ch->max_inbox_size = cmd_cache_ent_size[k];
		for (i = 0; i < ch->num_ent; i++) {
			msg = mlx5_alloc_cmd_msg(dev, GFP_KERNEL | __GFP_NOWARN,
						 ch->max_inbox_size, 0);
			if (IS_ERR(msg))
				break;
			msg->parent = ch;
			list_add_tail(&msg->list, &ch->head);
		}
	}
}