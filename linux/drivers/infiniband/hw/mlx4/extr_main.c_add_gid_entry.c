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
typedef  union ib_gid {int dummy; } ib_gid ;
struct mlx4_ib_qp {int /*<<< orphan*/  mutex; int /*<<< orphan*/  gid_list; int /*<<< orphan*/  port; } ;
struct mlx4_ib_gid_entry {int added; int /*<<< orphan*/  list; int /*<<< orphan*/  port; union ib_gid gid; } ;
struct mlx4_ib_dev {int dummy; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mlx4_ib_gid_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mlx4_ib_add_mc (struct mlx4_ib_dev*,struct mlx4_ib_qp*,union ib_gid*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx4_ib_qp* to_mqp (struct ib_qp*) ; 

__attribute__((used)) static int add_gid_entry(struct ib_qp *ibqp, union ib_gid *gid)
{
	struct mlx4_ib_qp *mqp = to_mqp(ibqp);
	struct mlx4_ib_dev *mdev = to_mdev(ibqp->device);
	struct mlx4_ib_gid_entry *ge;

	ge = kzalloc(sizeof *ge, GFP_KERNEL);
	if (!ge)
		return -ENOMEM;

	ge->gid = *gid;
	if (mlx4_ib_add_mc(mdev, mqp, gid)) {
		ge->port = mqp->port;
		ge->added = 1;
	}

	mutex_lock(&mqp->mutex);
	list_add_tail(&ge->list, &mqp->gid_list);
	mutex_unlock(&mqp->mutex);

	return 0;
}