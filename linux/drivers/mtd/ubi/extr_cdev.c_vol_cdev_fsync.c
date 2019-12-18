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
struct ubi_volume_desc {TYPE_1__* vol; } ;
struct ubi_device {int /*<<< orphan*/  ubi_num; } ;
struct inode {int dummy; } ;
struct file {struct ubi_volume_desc* private_data; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct ubi_device* ubi; } ;

/* Variables and functions */
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int ubi_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vol_cdev_fsync(struct file *file, loff_t start, loff_t end,
			  int datasync)
{
	struct ubi_volume_desc *desc = file->private_data;
	struct ubi_device *ubi = desc->vol->ubi;
	struct inode *inode = file_inode(file);
	int err;
	inode_lock(inode);
	err = ubi_sync(ubi->ubi_num);
	inode_unlock(inode);
	return err;
}