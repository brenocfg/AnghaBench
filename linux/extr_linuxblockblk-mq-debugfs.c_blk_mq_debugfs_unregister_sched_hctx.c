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
struct blk_mq_hw_ctx {int /*<<< orphan*/ * sched_debugfs_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 

void blk_mq_debugfs_unregister_sched_hctx(struct blk_mq_hw_ctx *hctx)
{
	debugfs_remove_recursive(hctx->sched_debugfs_dir);
	hctx->sched_debugfs_dir = NULL;
}