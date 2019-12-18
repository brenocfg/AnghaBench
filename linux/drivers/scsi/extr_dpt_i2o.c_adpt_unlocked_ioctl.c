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
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  uint ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 long adpt_ioctl (struct inode*,struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adpt_mutex ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long adpt_unlocked_ioctl(struct file *file, uint cmd, ulong arg)
{
	struct inode *inode;
	long ret;
 
	inode = file_inode(file);
 
	mutex_lock(&adpt_mutex);
	ret = adpt_ioctl(inode, file, cmd, arg);
	mutex_unlock(&adpt_mutex);

	return ret;
}