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
struct res_mpt {TYPE_1__* mtt; } ;
struct mlx4_vhcr {int in_modifier; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int dummy; } ;
struct mlx4_cmd_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  RES_MPT ; 
 int /*<<< orphan*/  RES_MPT_MAPPED ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int mlx4_DMA_wrapper (struct mlx4_dev*,int,struct mlx4_vhcr*,struct mlx4_cmd_mailbox*,struct mlx4_cmd_mailbox*,struct mlx4_cmd_info*) ; 
 int mpt_mask (struct mlx4_dev*) ; 
 int mr_res_start_move_to (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,struct res_mpt**) ; 
 int /*<<< orphan*/  res_abort_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  res_end_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 

int mlx4_HW2SW_MPT_wrapper(struct mlx4_dev *dev, int slave,
			   struct mlx4_vhcr *vhcr,
			   struct mlx4_cmd_mailbox *inbox,
			   struct mlx4_cmd_mailbox *outbox,
			   struct mlx4_cmd_info *cmd)
{
	int err;
	int index = vhcr->in_modifier;
	struct res_mpt *mpt;
	int id;

	id = index & mpt_mask(dev);
	err = mr_res_start_move_to(dev, slave, id, RES_MPT_MAPPED, &mpt);
	if (err)
		return err;

	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	if (err)
		goto ex_abort;

	if (mpt->mtt)
		atomic_dec(&mpt->mtt->ref_count);

	res_end_move(dev, slave, RES_MPT, id);
	return 0;

ex_abort:
	res_abort_move(dev, slave, RES_MPT, id);

	return err;
}