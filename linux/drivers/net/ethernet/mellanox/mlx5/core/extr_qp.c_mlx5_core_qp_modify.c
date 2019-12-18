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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_core_qp {int /*<<< orphan*/  uid; int /*<<< orphan*/  qpn; } ;
struct mlx5_core_dev {int dummy; } ;
struct mbox_info {int /*<<< orphan*/  outlen; int /*<<< orphan*/  out; int /*<<< orphan*/  inlen; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbox_free (struct mbox_info*) ; 
 int mlx5_cmd_exec (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int modify_qp_mbox_alloc (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct mbox_info*,int /*<<< orphan*/ ) ; 

int mlx5_core_qp_modify(struct mlx5_core_dev *dev, u16 opcode,
			u32 opt_param_mask, void *qpc,
			struct mlx5_core_qp *qp)
{
	struct mbox_info mbox;
	int err;

	err = modify_qp_mbox_alloc(dev, opcode, qp->qpn,
				   opt_param_mask, qpc, &mbox, qp->uid);
	if (err)
		return err;

	err = mlx5_cmd_exec(dev, mbox.in, mbox.inlen, mbox.out, mbox.outlen);
	mbox_free(&mbox);
	return err;
}