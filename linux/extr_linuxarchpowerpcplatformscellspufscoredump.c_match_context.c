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
struct spu_context {int flags; } ;
struct file {int /*<<< orphan*/ * f_op; } ;
struct TYPE_2__ {struct spu_context* i_ctx; } ;

/* Variables and functions */
 TYPE_1__* SPUFS_I (int /*<<< orphan*/ ) ; 
 int SPU_CREATE_NOSCHED ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  spufs_context_fops ; 

__attribute__((used)) static int match_context(const void *v, struct file *file, unsigned fd)
{
	struct spu_context *ctx;
	if (file->f_op != &spufs_context_fops)
		return 0;
	ctx = SPUFS_I(file_inode(file))->i_ctx;
	if (ctx->flags & SPU_CREATE_NOSCHED)
		return 0;
	return fd + 1;
}