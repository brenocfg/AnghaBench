#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ib_xrcd {int dummy; } ;
struct mlx4_ib_xrcd {int /*<<< orphan*/  xrcdn; int /*<<< orphan*/  pd; struct ib_xrcd ibxrcd; int /*<<< orphan*/  cq; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct ib_device {int dummy; } ;
struct ib_cq_init_attr {int cqe; } ;
struct TYPE_5__ {int flags; } ;
struct TYPE_7__ {TYPE_1__ caps; } ;
struct TYPE_6__ {TYPE_3__* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSYS ; 
 struct ib_xrcd* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MLX4_DEV_CAP_FLAG_XRC ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_alloc_pd (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_create_cq (struct ib_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct mlx4_ib_xrcd*,struct ib_cq_init_attr*) ; 
 int /*<<< orphan*/  ib_dealloc_pd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx4_ib_xrcd*) ; 
 struct mlx4_ib_xrcd* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mlx4_xrcd_alloc (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_xrcd_free (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* to_mdev (struct ib_device*) ; 

__attribute__((used)) static struct ib_xrcd *mlx4_ib_alloc_xrcd(struct ib_device *ibdev,
					  struct ib_ucontext *context,
					  struct ib_udata *udata)
{
	struct mlx4_ib_xrcd *xrcd;
	struct ib_cq_init_attr cq_attr = {};
	int err;

	if (!(to_mdev(ibdev)->dev->caps.flags & MLX4_DEV_CAP_FLAG_XRC))
		return ERR_PTR(-ENOSYS);

	xrcd = kmalloc(sizeof *xrcd, GFP_KERNEL);
	if (!xrcd)
		return ERR_PTR(-ENOMEM);

	err = mlx4_xrcd_alloc(to_mdev(ibdev)->dev, &xrcd->xrcdn);
	if (err)
		goto err1;

	xrcd->pd = ib_alloc_pd(ibdev, 0);
	if (IS_ERR(xrcd->pd)) {
		err = PTR_ERR(xrcd->pd);
		goto err2;
	}

	cq_attr.cqe = 1;
	xrcd->cq = ib_create_cq(ibdev, NULL, NULL, xrcd, &cq_attr);
	if (IS_ERR(xrcd->cq)) {
		err = PTR_ERR(xrcd->cq);
		goto err3;
	}

	return &xrcd->ibxrcd;

err3:
	ib_dealloc_pd(xrcd->pd);
err2:
	mlx4_xrcd_free(to_mdev(ibdev)->dev, xrcd->xrcdn);
err1:
	kfree(xrcd);
	return ERR_PTR(err);
}