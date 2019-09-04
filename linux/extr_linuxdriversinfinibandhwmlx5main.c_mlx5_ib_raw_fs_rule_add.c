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
struct mlx5_ib_flow_prio {struct mlx5_ib_flow_matcher* flow_matcher; } ;
struct mlx5_ib_flow_matcher {int priority; scalar_t__ flow_type; int /*<<< orphan*/  usecnt; } ;
struct mlx5_ib_flow_handler {struct mlx5_ib_flow_matcher* flow_matcher; } ;
struct mlx5_ib_dev {TYPE_1__* flow_db; } ;
struct mlx5_flow_destination {int type; int tir_num; int ft_num; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 struct mlx5_ib_flow_prio* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mlx5_ib_flow_prio*) ; 
 int MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE_NUM ; 
 int MLX5_FLOW_DESTINATION_TYPE_TIR ; 
 int MLX5_IB_FLOW_LAST_PRIO ; 
 scalar_t__ MLX5_IB_FLOW_TYPE_NORMAL ; 
 int PTR_ERR (struct mlx5_ib_flow_prio*) ; 
 struct mlx5_ib_flow_prio* _create_raw_flow_rule (struct mlx5_ib_dev*,struct mlx5_ib_flow_prio*,struct mlx5_flow_destination*,struct mlx5_ib_flow_matcher*,void*,int) ; 
 struct mlx5_ib_flow_prio* _get_flow_table (struct mlx5_ib_dev*,int,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlx5_flow_destination*) ; 
 struct mlx5_flow_destination* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_flow_table (struct mlx5_ib_dev*,struct mlx5_ib_flow_prio*,int) ; 
 int raw_fs_is_multicast (struct mlx5_ib_flow_matcher*,void*) ; 

struct mlx5_ib_flow_handler *
mlx5_ib_raw_fs_rule_add(struct mlx5_ib_dev *dev,
			struct mlx5_ib_flow_matcher *fs_matcher,
			void *cmd_in, int inlen, int dest_id,
			int dest_type)
{
	struct mlx5_flow_destination *dst;
	struct mlx5_ib_flow_prio *ft_prio;
	int priority = fs_matcher->priority;
	struct mlx5_ib_flow_handler *handler;
	bool mcast;
	int err;

	if (fs_matcher->flow_type != MLX5_IB_FLOW_TYPE_NORMAL)
		return ERR_PTR(-EOPNOTSUPP);

	if (fs_matcher->priority > MLX5_IB_FLOW_LAST_PRIO)
		return ERR_PTR(-ENOMEM);

	dst = kzalloc(sizeof(*dst), GFP_KERNEL);
	if (!dst)
		return ERR_PTR(-ENOMEM);

	mcast = raw_fs_is_multicast(fs_matcher, cmd_in);
	mutex_lock(&dev->flow_db->lock);

	ft_prio = _get_flow_table(dev, priority, mcast);
	if (IS_ERR(ft_prio)) {
		err = PTR_ERR(ft_prio);
		goto unlock;
	}

	if (dest_type == MLX5_FLOW_DESTINATION_TYPE_TIR) {
		dst->type = dest_type;
		dst->tir_num = dest_id;
	} else {
		dst->type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE_NUM;
		dst->ft_num = dest_id;
	}

	handler = _create_raw_flow_rule(dev, ft_prio, dst, fs_matcher, cmd_in,
					inlen);

	if (IS_ERR(handler)) {
		err = PTR_ERR(handler);
		goto destroy_ft;
	}

	mutex_unlock(&dev->flow_db->lock);
	atomic_inc(&fs_matcher->usecnt);
	handler->flow_matcher = fs_matcher;

	kfree(dst);

	return handler;

destroy_ft:
	put_flow_table(dev, ft_prio, false);
unlock:
	mutex_unlock(&dev->flow_db->lock);
	kfree(dst);

	return ERR_PTR(err);
}