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
struct mlx5_srq_attr {int /*<<< orphan*/  lwm; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_gs; scalar_t__ max; } ;
struct mlx5_ib_srq {TYPE_1__ msrq; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_srq_attr {int /*<<< orphan*/  max_sge; scalar_t__ max_wr; int /*<<< orphan*/  srq_limit; } ;
struct ib_srq {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mlx5_srq_attr*) ; 
 struct mlx5_srq_attr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_core_query_srq (int /*<<< orphan*/ ,TYPE_1__*,struct mlx5_srq_attr*) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_srq* to_msrq (struct ib_srq*) ; 

int mlx5_ib_query_srq(struct ib_srq *ibsrq, struct ib_srq_attr *srq_attr)
{
	struct mlx5_ib_dev *dev = to_mdev(ibsrq->device);
	struct mlx5_ib_srq *srq = to_msrq(ibsrq);
	int ret;
	struct mlx5_srq_attr *out;

	out = kzalloc(sizeof(*out), GFP_KERNEL);
	if (!out)
		return -ENOMEM;

	ret = mlx5_core_query_srq(dev->mdev, &srq->msrq, out);
	if (ret)
		goto out_box;

	srq_attr->srq_limit = out->lwm;
	srq_attr->max_wr    = srq->msrq.max - 1;
	srq_attr->max_sge   = srq->msrq.max_gs;

out_box:
	kfree(out);
	return ret;
}