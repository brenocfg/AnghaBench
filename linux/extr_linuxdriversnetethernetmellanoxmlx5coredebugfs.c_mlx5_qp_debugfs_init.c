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
struct TYPE_2__ {int /*<<< orphan*/  qp_debugfs; int /*<<< orphan*/  dbg_root; } ;
struct mlx5_core_dev {TYPE_1__ priv; int /*<<< orphan*/  num_qps; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_debugfs_root ; 

int mlx5_qp_debugfs_init(struct mlx5_core_dev *dev)
{
	if (!mlx5_debugfs_root)
		return 0;

	atomic_set(&dev->num_qps, 0);

	dev->priv.qp_debugfs = debugfs_create_dir("QPs",  dev->priv.dbg_root);
	if (!dev->priv.qp_debugfs)
		return -ENOMEM;

	return 0;
}