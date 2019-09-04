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
typedef  int /*<<< orphan*/  u16 ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cq_context {void* cq_period; void* cq_max_count; } ;
struct mlx4_cq {int /*<<< orphan*/  cqn; } ;
struct mlx4_cmd_mailbox {struct mlx4_cq_context* buf; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int mlx4_MODIFY_CQ (struct mlx4_dev*,struct mlx4_cmd_mailbox*,int /*<<< orphan*/ ,int) ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 

int mlx4_cq_modify(struct mlx4_dev *dev, struct mlx4_cq *cq,
		   u16 count, u16 period)
{
	struct mlx4_cmd_mailbox *mailbox;
	struct mlx4_cq_context *cq_context;
	int err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);

	cq_context = mailbox->buf;
	cq_context->cq_max_count = cpu_to_be16(count);
	cq_context->cq_period    = cpu_to_be16(period);

	err = mlx4_MODIFY_CQ(dev, mailbox, cq->cqn, 1);

	mlx4_free_cmd_mailbox(dev, mailbox);
	return err;
}