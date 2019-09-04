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
struct ib_pd {int dummy; } ;
struct mlx5_ib_pd {struct ib_pd ibpd; int /*<<< orphan*/  pdn; } ;
struct mlx5_ib_alloc_pd_resp {int /*<<< orphan*/  pdn; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
struct TYPE_2__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 struct ib_pd* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ib_copy_to_udata (struct ib_udata*,struct mlx5_ib_alloc_pd_resp*,int) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_pd*) ; 
 struct mlx5_ib_pd* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_core_alloc_pd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_dealloc_pd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_mdev (struct ib_device*) ; 

__attribute__((used)) static struct ib_pd *mlx5_ib_alloc_pd(struct ib_device *ibdev,
				      struct ib_ucontext *context,
				      struct ib_udata *udata)
{
	struct mlx5_ib_alloc_pd_resp resp;
	struct mlx5_ib_pd *pd;
	int err;

	pd = kmalloc(sizeof(*pd), GFP_KERNEL);
	if (!pd)
		return ERR_PTR(-ENOMEM);

	err = mlx5_core_alloc_pd(to_mdev(ibdev)->mdev, &pd->pdn);
	if (err) {
		kfree(pd);
		return ERR_PTR(err);
	}

	if (context) {
		resp.pdn = pd->pdn;
		if (ib_copy_to_udata(udata, &resp, sizeof(resp))) {
			mlx5_core_dealloc_pd(to_mdev(ibdev)->mdev, pd->pdn);
			kfree(pd);
			return ERR_PTR(-EFAULT);
		}
	}

	return &pd->ibpd;
}