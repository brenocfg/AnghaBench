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
struct TYPE_2__ {struct dentry* dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_file_get (struct dentry*) ; 
 int /*<<< orphan*/  debugfs_file_put (struct dentry*) ; 
 int /*<<< orphan*/  seq_lseek (struct file*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

loff_t hfi1_seq_lseek(struct file *file, loff_t offset, int whence)
{
	struct dentry *d = file->f_path.dentry;
	loff_t r;

	r = debugfs_file_get(d);
	if (unlikely(r))
		return r;
	r = seq_lseek(file, offset, whence);
	debugfs_file_put(d);
	return r;
}