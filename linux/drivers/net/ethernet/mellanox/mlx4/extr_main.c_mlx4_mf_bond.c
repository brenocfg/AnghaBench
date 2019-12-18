#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx4_slaves_pport {int /*<<< orphan*/  slaves; } ;
struct TYPE_4__ {scalar_t__ steering_mode; } ;
struct mlx4_dev {TYPE_2__ caps; TYPE_1__* persist; } ;
struct TYPE_3__ {scalar_t__ num_vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_BITMAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int MAX_MF_BOND_ALLOWED_SLAVES ; 
 int /*<<< orphan*/  MLX4_MFUNC_MAX ; 
 scalar_t__ MLX4_STEERING_MODE_DEVICE_MANAGED ; 
 int /*<<< orphan*/  bitmap_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int bitmap_weight (int /*<<< orphan*/ ,scalar_t__) ; 
 int mlx4_bond_fs_rules (struct mlx4_dev*) ; 
 int mlx4_bond_mac_table (struct mlx4_dev*) ; 
 int mlx4_bond_vlan_table (struct mlx4_dev*) ; 
 struct mlx4_slaves_pport mlx4_phys_to_slaves_pport (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  mlx4_unbond_mac_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_unbond_vlan_table (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,...) ; 
 int /*<<< orphan*/  slaves_port_1_2 ; 

__attribute__((used)) static int mlx4_mf_bond(struct mlx4_dev *dev)
{
	int err = 0;
	int nvfs;
	struct mlx4_slaves_pport slaves_port1;
	struct mlx4_slaves_pport slaves_port2;
	DECLARE_BITMAP(slaves_port_1_2, MLX4_MFUNC_MAX);

	slaves_port1 = mlx4_phys_to_slaves_pport(dev, 1);
	slaves_port2 = mlx4_phys_to_slaves_pport(dev, 2);
	bitmap_and(slaves_port_1_2,
		   slaves_port1.slaves, slaves_port2.slaves,
		   dev->persist->num_vfs + 1);

	/* only single port vfs are allowed */
	if (bitmap_weight(slaves_port_1_2, dev->persist->num_vfs + 1) > 1) {
		mlx4_warn(dev, "HA mode unsupported for dual ported VFs\n");
		return -EINVAL;
	}

	/* number of virtual functions is number of total functions minus one
	 * physical function for each port.
	 */
	nvfs = bitmap_weight(slaves_port1.slaves, dev->persist->num_vfs + 1) +
		bitmap_weight(slaves_port2.slaves, dev->persist->num_vfs + 1) - 2;

	/* limit on maximum allowed VFs */
	if (nvfs > MAX_MF_BOND_ALLOWED_SLAVES) {
		mlx4_warn(dev, "HA mode is not supported for %d VFs (max %d are allowed)\n",
			  nvfs, MAX_MF_BOND_ALLOWED_SLAVES);
		return -EINVAL;
	}

	if (dev->caps.steering_mode != MLX4_STEERING_MODE_DEVICE_MANAGED) {
		mlx4_warn(dev, "HA mode unsupported for NON DMFS steering\n");
		return -EINVAL;
	}

	err = mlx4_bond_mac_table(dev);
	if (err)
		return err;
	err = mlx4_bond_vlan_table(dev);
	if (err)
		goto err1;
	err = mlx4_bond_fs_rules(dev);
	if (err)
		goto err2;

	return 0;
err2:
	(void)mlx4_unbond_vlan_table(dev);
err1:
	(void)mlx4_unbond_mac_table(dev);
	return err;
}