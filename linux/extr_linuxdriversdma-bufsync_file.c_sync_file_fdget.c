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
struct sync_file {int dummy; } ;
struct file {struct sync_file* private_data; int /*<<< orphan*/ * f_op; } ;

/* Variables and functions */
 struct file* fget (int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  sync_file_fops ; 

__attribute__((used)) static struct sync_file *sync_file_fdget(int fd)
{
	struct file *file = fget(fd);

	if (!file)
		return NULL;

	if (file->f_op != &sync_file_fops)
		goto err;

	return file->private_data;

err:
	fput(file);
	return NULL;
}