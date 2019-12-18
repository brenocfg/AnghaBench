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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_ib_dev {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 struct mlx5_core_dev* mlx5_ib_get_native_port_mdev (struct mlx5_ib_dev*,int,int*) ; 
 int /*<<< orphan*/  mlx5_ib_put_native_port_mdev (struct mlx5_ib_dev*,int) ; 
 int mlx5_query_hca_vport_pkey (struct mlx5_core_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mlx5_ib_dev* to_mdev (struct ib_device*) ; 

__attribute__((used)) static int mlx5_query_hca_nic_pkey(struct ib_device *ibdev, u8 port,
				   u16 index, u16 *pkey)
{
	struct mlx5_ib_dev *dev = to_mdev(ibdev);
	struct mlx5_core_dev *mdev;
	bool put_mdev = true;
	u8 mdev_port_num;
	int err;

	mdev = mlx5_ib_get_native_port_mdev(dev, port, &mdev_port_num);
	if (!mdev) {
		/* The port isn't affiliated yet, get the PKey from the master
		 * port. For RoCE the PKey tables will be the same.
		 */
		put_mdev = false;
		mdev = dev->mdev;
		mdev_port_num = 1;
	}

	err = mlx5_query_hca_vport_pkey(mdev, 0, mdev_port_num, 0,
					index, pkey);
	if (put_mdev)
		mlx5_ib_put_native_port_mdev(dev, port);

	return err;
}