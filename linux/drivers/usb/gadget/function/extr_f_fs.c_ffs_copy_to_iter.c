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
typedef  int ssize_t ;

/* Variables and functions */
 int EFAULT ; 
 int copy_to_iter (void*,int,struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ffs_copy_to_iter(void *data, int data_len, struct iov_iter *iter)
{
	ssize_t ret = copy_to_iter(data, data_len, iter);
	if (likely(ret == data_len))
		return ret;

	if (unlikely(iov_iter_count(iter)))
		return -EFAULT;

	/*
	 * Dear user space developer!
	 *
	 * TL;DR: To stop getting below error message in your kernel log, change
	 * user space code using functionfs to align read buffers to a max
	 * packet size.
	 *
	 * Some UDCs (e.g. dwc3) require request sizes to be a multiple of a max
	 * packet size.  When unaligned buffer is passed to functionfs, it
	 * internally uses a larger, aligned buffer so that such UDCs are happy.
	 *
	 * Unfortunately, this means that host may send more data than was
	 * requested in read(2) system call.  f_fs doesn’t know what to do with
	 * that excess data so it simply drops it.
	 *
	 * Was the buffer aligned in the first place, no such problem would
	 * happen.
	 *
	 * Data may be dropped only in AIO reads.  Synchronous reads are handled
	 * by splitting a request into multiple parts.  This splitting may still
	 * be a problem though so it’s likely best to align the buffer
	 * regardless of it being AIO or not..
	 *
	 * This only affects OUT endpoints, i.e. reading data with a read(2),
	 * aio_read(2) etc. system calls.  Writing data to an IN endpoint is not
	 * affected.
	 */
	pr_err("functionfs read size %d > requested size %zd, dropping excess data. "
	       "Align read buffer size to max packet size to avoid the problem.\n",
	       data_len, ret);

	return ret;
}