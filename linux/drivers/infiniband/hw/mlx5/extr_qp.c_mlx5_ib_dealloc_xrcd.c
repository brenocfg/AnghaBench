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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_xrcd {int /*<<< orphan*/  device; } ;
struct ib_udata {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  xrcdn; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ib_xrcd*) ; 
 int mlx5_cmd_xrcd_dealloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_mxrcd (struct ib_xrcd*) ; 

int mlx5_ib_dealloc_xrcd(struct ib_xrcd *xrcd, struct ib_udata *udata)
{
	struct mlx5_ib_dev *dev = to_mdev(xrcd->device);
	u32 xrcdn = to_mxrcd(xrcd)->xrcdn;
	int err;

	err = mlx5_cmd_xrcd_dealloc(dev->mdev, xrcdn, 0);
	if (err)
		mlx5_ib_warn(dev, "failed to dealloc xrcdn 0x%x\n", xrcdn);

	kfree(xrcd);
	return 0;
}