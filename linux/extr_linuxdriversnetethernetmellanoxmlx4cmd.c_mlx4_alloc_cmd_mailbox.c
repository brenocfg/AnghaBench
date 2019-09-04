#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  buf; int /*<<< orphan*/  dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  pool; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mlx4_cmd_mailbox* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlx4_cmd_mailbox*) ; 
 struct mlx4_cmd_mailbox* kmalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* mlx4_priv (struct mlx4_dev*) ; 

struct mlx4_cmd_mailbox *mlx4_alloc_cmd_mailbox(struct mlx4_dev *dev)
{
	struct mlx4_cmd_mailbox *mailbox;

	mailbox = kmalloc(sizeof(*mailbox), GFP_KERNEL);
	if (!mailbox)
		return ERR_PTR(-ENOMEM);

	mailbox->buf = dma_pool_zalloc(mlx4_priv(dev)->cmd.pool, GFP_KERNEL,
				       &mailbox->dma);
	if (!mailbox->buf) {
		kfree(mailbox);
		return ERR_PTR(-ENOMEM);
	}

	return mailbox;
}