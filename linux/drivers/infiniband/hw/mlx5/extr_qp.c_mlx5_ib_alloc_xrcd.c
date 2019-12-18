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
struct ib_xrcd {int dummy; } ;
struct mlx5_ib_xrcd {struct ib_xrcd ibxrcd; int /*<<< orphan*/  xrcdn; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_udata {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 struct ib_xrcd* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_xrcd*) ; 
 struct mlx5_ib_xrcd* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_cmd_xrcd_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* to_mdev (struct ib_device*) ; 
 int /*<<< orphan*/  xrc ; 

struct ib_xrcd *mlx5_ib_alloc_xrcd(struct ib_device *ibdev,
				   struct ib_udata *udata)
{
	struct mlx5_ib_dev *dev = to_mdev(ibdev);
	struct mlx5_ib_xrcd *xrcd;
	int err;

	if (!MLX5_CAP_GEN(dev->mdev, xrc))
		return ERR_PTR(-ENOSYS);

	xrcd = kmalloc(sizeof(*xrcd), GFP_KERNEL);
	if (!xrcd)
		return ERR_PTR(-ENOMEM);

	err = mlx5_cmd_xrcd_alloc(dev->mdev, &xrcd->xrcdn, 0);
	if (err) {
		kfree(xrcd);
		return ERR_PTR(-ENOMEM);
	}

	return &xrcd->ibxrcd;
}