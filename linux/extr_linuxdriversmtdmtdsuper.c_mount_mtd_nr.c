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
struct file_system_type {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* ERR_CAST (struct mtd_info*) ; 
 scalar_t__ IS_ERR (struct mtd_info*) ; 
 struct mtd_info* get_mtd_device (int /*<<< orphan*/ *,int) ; 
 struct dentry* mount_mtd_aux (struct file_system_type*,int,char const*,void*,struct mtd_info*,int (*) (struct super_block*,void*,int)) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static struct dentry *mount_mtd_nr(struct file_system_type *fs_type, int flags,
			 const char *dev_name, void *data, int mtdnr,
			 int (*fill_super)(struct super_block *, void *, int))
{
	struct mtd_info *mtd;

	mtd = get_mtd_device(NULL, mtdnr);
	if (IS_ERR(mtd)) {
		pr_debug("MTDSB: Device #%u doesn't appear to exist\n", mtdnr);
		return ERR_CAST(mtd);
	}

	return mount_mtd_aux(fs_type, flags, dev_name, data, mtd, fill_super);
}