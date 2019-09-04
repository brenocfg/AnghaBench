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
struct mlx5_cmd_mailbox {int /*<<< orphan*/  dma; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_cmd_mailbox*) ; 

__attribute__((used)) static void free_cmd_box(struct mlx5_core_dev *dev,
			 struct mlx5_cmd_mailbox *mailbox)
{
	dma_pool_free(dev->cmd.pool, mailbox->buf, mailbox->dma);
	kfree(mailbox);
}