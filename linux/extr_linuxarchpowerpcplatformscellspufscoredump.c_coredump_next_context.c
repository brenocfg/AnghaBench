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
struct spu_context {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_4__ {struct spu_context* i_ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  files; } ;

/* Variables and functions */
 TYPE_2__* SPUFS_I (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 struct file* fcheck (int) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int iterate_fd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  match_context ; 

__attribute__((used)) static struct spu_context *coredump_next_context(int *fd)
{
	struct file *file;
	int n = iterate_fd(current->files, *fd, match_context, NULL);
	if (!n)
		return NULL;
	*fd = n - 1;
	file = fcheck(*fd);
	return SPUFS_I(file_inode(file))->i_ctx;
}