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
struct ffs_epfile {int /*<<< orphan*/  read_buffer; } ;
struct ffs_buffer {int dummy; } ;

/* Variables and functions */
 struct ffs_buffer* READ_BUFFER_DROP ; 
 int /*<<< orphan*/  kfree (struct ffs_buffer*) ; 
 struct ffs_buffer* xchg (int /*<<< orphan*/ *,struct ffs_buffer*) ; 

__attribute__((used)) static void __ffs_epfile_read_buffer_free(struct ffs_epfile *epfile)
{
	/*
	 * See comment in struct ffs_epfile for full read_buffer pointer
	 * synchronisation story.
	 */
	struct ffs_buffer *buf = xchg(&epfile->read_buffer, READ_BUFFER_DROP);
	if (buf && buf != READ_BUFFER_DROP)
		kfree(buf);
}