#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {TYPE_2__ wc_head; TYPE_1__ reg_head; } ;
struct mlx5_priv {int /*<<< orphan*/  dbg_root; int /*<<< orphan*/  mkey_lock; int /*<<< orphan*/  pgdir_list; int /*<<< orphan*/  pgdir_mutex; int /*<<< orphan*/  alloc_mutex; TYPE_3__ bfregs; int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/  ctx_list; } ;
struct mlx5_core_dev {struct mlx5_priv priv; int /*<<< orphan*/  device; int /*<<< orphan*/  intf_state_mutex; int /*<<< orphan*/ * profile; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_debugfs_root ; 
 int /*<<< orphan*/  mlx5_health_cleanup (struct mlx5_core_dev*) ; 
 int mlx5_health_init (struct mlx5_core_dev*) ; 
 int mlx5_pagealloc_init (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * profile ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5_mdev_init(struct mlx5_core_dev *dev, int profile_idx)
{
	struct mlx5_priv *priv = &dev->priv;
	int err;

	dev->profile = &profile[profile_idx];

	INIT_LIST_HEAD(&priv->ctx_list);
	spin_lock_init(&priv->ctx_lock);
	mutex_init(&dev->intf_state_mutex);

	mutex_init(&priv->bfregs.reg_head.lock);
	mutex_init(&priv->bfregs.wc_head.lock);
	INIT_LIST_HEAD(&priv->bfregs.reg_head.list);
	INIT_LIST_HEAD(&priv->bfregs.wc_head.list);

	mutex_init(&priv->alloc_mutex);
	mutex_init(&priv->pgdir_mutex);
	INIT_LIST_HEAD(&priv->pgdir_list);
	spin_lock_init(&priv->mkey_lock);

	priv->dbg_root = debugfs_create_dir(dev_name(dev->device),
					    mlx5_debugfs_root);
	if (!priv->dbg_root) {
		dev_err(dev->device, "mlx5_core: error, Cannot create debugfs dir, aborting\n");
		return -ENOMEM;
	}

	err = mlx5_health_init(dev);
	if (err)
		goto err_health_init;

	err = mlx5_pagealloc_init(dev);
	if (err)
		goto err_pagealloc_init;

	return 0;

err_pagealloc_init:
	mlx5_health_cleanup(dev);
err_health_init:
	debugfs_remove(dev->priv.dbg_root);

	return err;
}