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
struct mtd_info {scalar_t__ type; int flags; } ;
struct mtd_file_info {struct mtd_info* mtd; } ;
struct inode {int dummy; } ;
struct file {int f_mode; struct mtd_file_info* private_data; } ;

/* Variables and functions */
 int EACCES ; 
 int ENODEV ; 
 int ENOMEM ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mtd_info*) ; 
 scalar_t__ MTD_ABSENT ; 
 int MTD_WRITEABLE ; 
 int PTR_ERR (struct mtd_info*) ; 
 struct mtd_info* get_mtd_device (int /*<<< orphan*/ *,int) ; 
 int iminor (struct inode*) ; 
 struct mtd_file_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  put_mtd_device (struct mtd_info*) ; 

__attribute__((used)) static int mtdchar_open(struct inode *inode, struct file *file)
{
	int minor = iminor(inode);
	int devnum = minor >> 1;
	int ret = 0;
	struct mtd_info *mtd;
	struct mtd_file_info *mfi;

	pr_debug("MTD_open\n");

	/* You can't open the RO devices RW */
	if ((file->f_mode & FMODE_WRITE) && (minor & 1))
		return -EACCES;

	mutex_lock(&mtd_mutex);
	mtd = get_mtd_device(NULL, devnum);

	if (IS_ERR(mtd)) {
		ret = PTR_ERR(mtd);
		goto out;
	}

	if (mtd->type == MTD_ABSENT) {
		ret = -ENODEV;
		goto out1;
	}

	/* You can't open it RW if it's not a writeable device */
	if ((file->f_mode & FMODE_WRITE) && !(mtd->flags & MTD_WRITEABLE)) {
		ret = -EACCES;
		goto out1;
	}

	mfi = kzalloc(sizeof(*mfi), GFP_KERNEL);
	if (!mfi) {
		ret = -ENOMEM;
		goto out1;
	}
	mfi->mtd = mtd;
	file->private_data = mfi;
	mutex_unlock(&mtd_mutex);
	return 0;

out1:
	put_mtd_device(mtd);
out:
	mutex_unlock(&mtd_mutex);
	return ret;
}