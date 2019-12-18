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
struct iov_iter {int dummy; } ;
struct ffs_epfile {int /*<<< orphan*/  read_buffer; } ;
struct ffs_buffer {scalar_t__ data; scalar_t__ length; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EFAULT ; 
 struct ffs_buffer* READ_BUFFER_DROP ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ffs_buffer*) ; 
 scalar_t__ copy_to_iter (scalar_t__,scalar_t__,struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  kfree (struct ffs_buffer*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct ffs_buffer* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t __ffs_epfile_read_buffered(struct ffs_epfile *epfile,
					  struct iov_iter *iter)
{
	/*
	 * Null out epfile->read_buffer so ffs_func_eps_disable does not free
	 * the buffer while we are using it.  See comment in struct ffs_epfile
	 * for full read_buffer pointer synchronisation story.
	 */
	struct ffs_buffer *buf = xchg(&epfile->read_buffer, NULL);
	ssize_t ret;
	if (!buf || buf == READ_BUFFER_DROP)
		return 0;

	ret = copy_to_iter(buf->data, buf->length, iter);
	if (buf->length == ret) {
		kfree(buf);
		return ret;
	}

	if (unlikely(iov_iter_count(iter))) {
		ret = -EFAULT;
	} else {
		buf->length -= ret;
		buf->data += ret;
	}

	if (cmpxchg(&epfile->read_buffer, NULL, buf))
		kfree(buf);

	return ret;
}