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
struct pci_device_id {int driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mlx5_core_dev {int /*<<< orphan*/  coredev_type; struct pci_dev* pdev; int /*<<< orphan*/ * device; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MLX5_COREDEV_PF ; 
 int /*<<< orphan*/  MLX5_COREDEV_VF ; 
 int /*<<< orphan*/  MLX5_IB_MOD ; 
 int MLX5_PCI_DEV_IS_VF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct mlx5_core_dev* devlink_priv (struct devlink*) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int) ; 
 int mlx5_crdump_enable (struct mlx5_core_dev*) ; 
 struct devlink* mlx5_devlink_alloc () ; 
 int /*<<< orphan*/  mlx5_devlink_free (struct devlink*) ; 
 int mlx5_devlink_register (struct devlink*,int /*<<< orphan*/ *) ; 
 int mlx5_load_one (struct mlx5_core_dev*,int) ; 
 int mlx5_mdev_init (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_mdev_uninit (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_pci_close (struct mlx5_core_dev*) ; 
 int mlx5_pci_init (struct mlx5_core_dev*,struct pci_dev*,struct pci_device_id const*) ; 
 int /*<<< orphan*/  mlx5_unload_one (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  prof_sel ; 
 int /*<<< orphan*/  request_module_nowait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_one(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct mlx5_core_dev *dev;
	struct devlink *devlink;
	int err;

	devlink = mlx5_devlink_alloc();
	if (!devlink) {
		dev_err(&pdev->dev, "devlink alloc failed\n");
		return -ENOMEM;
	}

	dev = devlink_priv(devlink);
	dev->device = &pdev->dev;
	dev->pdev = pdev;

	dev->coredev_type = id->driver_data & MLX5_PCI_DEV_IS_VF ?
			 MLX5_COREDEV_VF : MLX5_COREDEV_PF;

	err = mlx5_mdev_init(dev, prof_sel);
	if (err)
		goto mdev_init_err;

	err = mlx5_pci_init(dev, pdev, id);
	if (err) {
		mlx5_core_err(dev, "mlx5_pci_init failed with error code %d\n",
			      err);
		goto pci_init_err;
	}

	err = mlx5_load_one(dev, true);
	if (err) {
		mlx5_core_err(dev, "mlx5_load_one failed with error code %d\n",
			      err);
		goto err_load_one;
	}

	request_module_nowait(MLX5_IB_MOD);

	err = mlx5_devlink_register(devlink, &pdev->dev);
	if (err)
		goto clean_load;

	err = mlx5_crdump_enable(dev);
	if (err)
		dev_err(&pdev->dev, "mlx5_crdump_enable failed with error code %d\n", err);

	pci_save_state(pdev);
	return 0;

clean_load:
	mlx5_unload_one(dev, true);

err_load_one:
	mlx5_pci_close(dev);
pci_init_err:
	mlx5_mdev_uninit(dev);
mdev_init_err:
	mlx5_devlink_free(devlink);

	return err;
}