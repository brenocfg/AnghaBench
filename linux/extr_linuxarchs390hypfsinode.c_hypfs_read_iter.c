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
struct kiocb {size_t ki_pos; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct file {char* private_data; } ;
typedef  size_t ssize_t ;
typedef  size_t loff_t ;

/* Variables and functions */
 size_t EFAULT ; 
 size_t EINVAL ; 
 size_t copy_to_iter (char*,size_t,struct iov_iter*) ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static ssize_t hypfs_read_iter(struct kiocb *iocb, struct iov_iter *to)
{
	struct file *file = iocb->ki_filp;
	char *data = file->private_data;
	size_t available = strlen(data);
	loff_t pos = iocb->ki_pos;
	size_t count;

	if (pos < 0)
		return -EINVAL;
	if (pos >= available || !iov_iter_count(to))
		return 0;
	count = copy_to_iter(data + pos, available - pos, to);
	if (!count)
		return -EFAULT;
	iocb->ki_pos = pos + count;
	file_accessed(file);
	return count;
}