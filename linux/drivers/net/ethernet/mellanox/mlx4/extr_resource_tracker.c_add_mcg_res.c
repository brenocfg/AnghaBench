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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct res_qp {int /*<<< orphan*/  mcg_spl; int /*<<< orphan*/  mcg_list; } ;
struct res_gid {int prot; int steer; int /*<<< orphan*/  list; int /*<<< orphan*/  reg_id; int /*<<< orphan*/  gid; } ;
struct mlx4_dev {int dummy; } ;
typedef  enum mlx4_steer_type { ____Placeholder_mlx4_steer_type } mlx4_steer_type ;
typedef  enum mlx4_protocol { ____Placeholder_mlx4_protocol } mlx4_protocol ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ find_gid (struct mlx4_dev*,int,struct res_qp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct res_gid*) ; 
 struct res_gid* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_mcg_res(struct mlx4_dev *dev, int slave, struct res_qp *rqp,
		       u8 *gid, enum mlx4_protocol prot,
		       enum mlx4_steer_type steer, u64 reg_id)
{
	struct res_gid *res;
	int err;

	res = kzalloc(sizeof(*res), GFP_KERNEL);
	if (!res)
		return -ENOMEM;

	spin_lock_irq(&rqp->mcg_spl);
	if (find_gid(dev, slave, rqp, gid)) {
		kfree(res);
		err = -EEXIST;
	} else {
		memcpy(res->gid, gid, 16);
		res->prot = prot;
		res->steer = steer;
		res->reg_id = reg_id;
		list_add_tail(&res->list, &rqp->mcg_list);
		err = 0;
	}
	spin_unlock_irq(&rqp->mcg_spl);

	return err;
}