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
struct pci_device_id {int /*<<< orphan*/  driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {TYPE_2__ wc_head; TYPE_1__ reg_head; } ;
struct mlx5_priv {int is_accum_events; TYPE_3__ bfregs; int /*<<< orphan*/  waiting_events_list; int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/  ctx_list; int /*<<< orphan*/  pci_dev_data; } ;
struct mlx5_core_dev {int /*<<< orphan*/  intf_state_mutex; int /*<<< orphan*/  pci_status_mutex; int /*<<< orphan*/ * profile; int /*<<< orphan*/  event; struct pci_dev* pdev; struct mlx5_priv priv; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX5_IB_MOD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct devlink* devlink_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devlink_free (struct devlink*) ; 
 struct mlx5_core_dev* devlink_priv (struct devlink*) ; 
 int devlink_register (struct devlink*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_event ; 
 int /*<<< orphan*/  mlx5_devlink_ops ; 
 int /*<<< orphan*/  mlx5_health_cleanup (struct mlx5_core_dev*) ; 
 int mlx5_health_init (struct mlx5_core_dev*) ; 
 int mlx5_load_one (struct mlx5_core_dev*,struct mlx5_priv*,int) ; 
 int /*<<< orphan*/  mlx5_pagealloc_cleanup (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_pagealloc_init (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_pci_close (struct mlx5_core_dev*,struct mlx5_priv*) ; 
 int mlx5_pci_init (struct mlx5_core_dev*,struct mlx5_priv*) ; 
 int /*<<< orphan*/  mlx5_unload_one (struct mlx5_core_dev*,struct mlx5_priv*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct mlx5_core_dev*) ; 
 size_t prof_sel ; 
 int /*<<< orphan*/ * profile ; 
 int /*<<< orphan*/  request_module_nowait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_one(struct pci_dev *pdev,
		    const struct pci_device_id *id)
{
	struct mlx5_core_dev *dev;
	struct devlink *devlink;
	struct mlx5_priv *priv;
	int err;

	devlink = devlink_alloc(&mlx5_devlink_ops, sizeof(*dev));
	if (!devlink) {
		dev_err(&pdev->dev, "kzalloc failed\n");
		return -ENOMEM;
	}

	dev = devlink_priv(devlink);
	priv = &dev->priv;
	priv->pci_dev_data = id->driver_data;

	pci_set_drvdata(pdev, dev);

	dev->pdev = pdev;
	dev->event = mlx5_core_event;
	dev->profile = &profile[prof_sel];

	INIT_LIST_HEAD(&priv->ctx_list);
	spin_lock_init(&priv->ctx_lock);
	mutex_init(&dev->pci_status_mutex);
	mutex_init(&dev->intf_state_mutex);

	INIT_LIST_HEAD(&priv->waiting_events_list);
	priv->is_accum_events = false;

#ifdef CONFIG_INFINIBAND_ON_DEMAND_PAGING
	err = init_srcu_struct(&priv->pfault_srcu);
	if (err) {
		dev_err(&pdev->dev, "init_srcu_struct failed with error code %d\n",
			err);
		goto clean_dev;
	}
#endif
	mutex_init(&priv->bfregs.reg_head.lock);
	mutex_init(&priv->bfregs.wc_head.lock);
	INIT_LIST_HEAD(&priv->bfregs.reg_head.list);
	INIT_LIST_HEAD(&priv->bfregs.wc_head.list);

	err = mlx5_pci_init(dev, priv);
	if (err) {
		dev_err(&pdev->dev, "mlx5_pci_init failed with error code %d\n", err);
		goto clean_srcu;
	}

	err = mlx5_health_init(dev);
	if (err) {
		dev_err(&pdev->dev, "mlx5_health_init failed with error code %d\n", err);
		goto close_pci;
	}

	mlx5_pagealloc_init(dev);

	err = mlx5_load_one(dev, priv, true);
	if (err) {
		dev_err(&pdev->dev, "mlx5_load_one failed with error code %d\n", err);
		goto clean_health;
	}

	request_module_nowait(MLX5_IB_MOD);

	err = devlink_register(devlink, &pdev->dev);
	if (err)
		goto clean_load;

	pci_save_state(pdev);
	return 0;

clean_load:
	mlx5_unload_one(dev, priv, true);
clean_health:
	mlx5_pagealloc_cleanup(dev);
	mlx5_health_cleanup(dev);
close_pci:
	mlx5_pci_close(dev, priv);
clean_srcu:
#ifdef CONFIG_INFINIBAND_ON_DEMAND_PAGING
	cleanup_srcu_struct(&priv->pfault_srcu);
clean_dev:
#endif
	devlink_free(devlink);

	return err;
}