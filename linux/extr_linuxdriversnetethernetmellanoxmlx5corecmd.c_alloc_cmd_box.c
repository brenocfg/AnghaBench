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
struct TYPE_2__ {int /*<<< orphan*/  pool; } ;
struct mlx5_core_dev {TYPE_1__ cmd; } ;
struct mlx5_cmd_mailbox {int /*<<< orphan*/ * next; int /*<<< orphan*/  buf; int /*<<< orphan*/  dma; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mlx5_cmd_mailbox* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlx5_cmd_mailbox*) ; 
 struct mlx5_cmd_mailbox* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*) ; 

__attribute__((used)) static struct mlx5_cmd_mailbox *alloc_cmd_box(struct mlx5_core_dev *dev,
					      gfp_t flags)
{
	struct mlx5_cmd_mailbox *mailbox;

	mailbox = kmalloc(sizeof(*mailbox), flags);
	if (!mailbox)
		return ERR_PTR(-ENOMEM);

	mailbox->buf = dma_pool_zalloc(dev->cmd.pool, flags,
				       &mailbox->dma);
	if (!mailbox->buf) {
		mlx5_core_dbg(dev, "failed allocation\n");
		kfree(mailbox);
		return ERR_PTR(-ENOMEM);
	}
	mailbox->next = NULL;

	return mailbox;
}