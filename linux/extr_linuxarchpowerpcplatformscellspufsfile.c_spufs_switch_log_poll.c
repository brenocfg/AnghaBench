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
struct spu_context {TYPE_1__* switch_log; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_4__ {struct spu_context* i_ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int EPOLLIN ; 
 TYPE_2__* SPUFS_I (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int spu_acquire (struct spu_context*) ; 
 int /*<<< orphan*/  spu_release (struct spu_context*) ; 
 scalar_t__ spufs_switch_log_used (struct spu_context*) ; 

__attribute__((used)) static __poll_t spufs_switch_log_poll(struct file *file, poll_table *wait)
{
	struct inode *inode = file_inode(file);
	struct spu_context *ctx = SPUFS_I(inode)->i_ctx;
	__poll_t mask = 0;
	int rc;

	poll_wait(file, &ctx->switch_log->wait, wait);

	rc = spu_acquire(ctx);
	if (rc)
		return rc;

	if (spufs_switch_log_used(ctx) > 0)
		mask |= EPOLLIN;

	spu_release(ctx);

	return mask;
}