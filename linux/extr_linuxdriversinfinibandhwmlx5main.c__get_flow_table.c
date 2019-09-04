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
struct mlx5_ib_flow_prio {scalar_t__ flow_table; } ;
struct mlx5_ib_dev {TYPE_1__* flow_db; int /*<<< orphan*/  mdev; } ;
struct mlx5_flow_namespace {int dummy; } ;
struct TYPE_2__ {struct mlx5_ib_flow_prio* prios; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOTSUPP ; 
 struct mlx5_ib_flow_prio* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_FLOWTABLE_NIC_RX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_FLOW_NAMESPACE_BYPASS ; 
 int MLX5_FS_MAX_ENTRIES ; 
 int /*<<< orphan*/  MLX5_FS_MAX_TYPES ; 
 int MLX5_IB_FLOW_MCAST_PRIO ; 
 struct mlx5_ib_flow_prio* _get_prio (struct mlx5_flow_namespace*,struct mlx5_ib_flow_prio*,int,int,int /*<<< orphan*/ ) ; 
 int ib_prio_to_core_prio (int,int) ; 
 int /*<<< orphan*/  log_max_ft_size ; 
 struct mlx5_flow_namespace* mlx5_get_flow_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlx5_ib_flow_prio *_get_flow_table(struct mlx5_ib_dev *dev,
						 int priority, bool mcast)
{
	int max_table_size;
	struct mlx5_flow_namespace *ns = NULL;
	struct mlx5_ib_flow_prio *prio;

	max_table_size = BIT(MLX5_CAP_FLOWTABLE_NIC_RX(dev->mdev,
			     log_max_ft_size));
	if (max_table_size < MLX5_FS_MAX_ENTRIES)
		return ERR_PTR(-ENOMEM);

	if (mcast)
		priority = MLX5_IB_FLOW_MCAST_PRIO;
	else
		priority = ib_prio_to_core_prio(priority, false);

	ns = mlx5_get_flow_namespace(dev->mdev, MLX5_FLOW_NAMESPACE_BYPASS);
	if (!ns)
		return ERR_PTR(-ENOTSUPP);

	prio = &dev->flow_db->prios[priority];

	if (prio->flow_table)
		return prio;

	return _get_prio(ns, prio, priority, MLX5_FS_MAX_ENTRIES,
			 MLX5_FS_MAX_TYPES);
}