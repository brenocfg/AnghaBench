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
struct mtd_info {int dummy; } ;
struct mtd_file_info {struct mtd_info* mtd; } ;
struct inode {int dummy; } ;
struct file {int f_mode; struct mtd_file_info* private_data; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int /*<<< orphan*/  kfree (struct mtd_file_info*) ; 
 int /*<<< orphan*/  mtd_sync (struct mtd_info*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  put_mtd_device (struct mtd_info*) ; 

__attribute__((used)) static int mtdchar_close(struct inode *inode, struct file *file)
{
	struct mtd_file_info *mfi = file->private_data;
	struct mtd_info *mtd = mfi->mtd;

	pr_debug("MTD_close\n");

	/* Only sync if opened RW */
	if ((file->f_mode & FMODE_WRITE))
		mtd_sync(mtd);

	put_mtd_device(mtd);
	file->private_data = NULL;
	kfree(mfi);

	return 0;
}