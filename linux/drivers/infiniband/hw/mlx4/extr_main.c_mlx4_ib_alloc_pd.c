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
struct mlx4_ib_pd {int /*<<< orphan*/  pdn; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {struct ib_device* device; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ ib_copy_to_udata (struct ib_udata*,int /*<<< orphan*/ *,int) ; 
 int mlx4_pd_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_pd_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_mdev (struct ib_device*) ; 
 struct mlx4_ib_pd* to_mpd (struct ib_pd*) ; 

__attribute__((used)) static int mlx4_ib_alloc_pd(struct ib_pd *ibpd, struct ib_udata *udata)
{
	struct mlx4_ib_pd *pd = to_mpd(ibpd);
	struct ib_device *ibdev = ibpd->device;
	int err;

	err = mlx4_pd_alloc(to_mdev(ibdev)->dev, &pd->pdn);
	if (err)
		return err;

	if (udata && ib_copy_to_udata(udata, &pd->pdn, sizeof(__u32))) {
		mlx4_pd_free(to_mdev(ibdev)->dev, pd->pdn);
		return -EFAULT;
	}
	return 0;
}