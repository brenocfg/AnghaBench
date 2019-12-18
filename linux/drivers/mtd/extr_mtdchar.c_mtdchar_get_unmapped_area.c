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
struct mtd_info {unsigned long size; } ;
struct mtd_file_info {struct mtd_info* mtd; } ;
struct file {struct mtd_file_info* private_data; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 unsigned long ENODEV ; 
 int EOPNOTSUPP ; 
 unsigned long PAGE_SHIFT ; 
 int mtd_get_unmapped_area (struct mtd_info*,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long mtdchar_get_unmapped_area(struct file *file,
					   unsigned long addr,
					   unsigned long len,
					   unsigned long pgoff,
					   unsigned long flags)
{
	struct mtd_file_info *mfi = file->private_data;
	struct mtd_info *mtd = mfi->mtd;
	unsigned long offset;
	int ret;

	if (addr != 0)
		return (unsigned long) -EINVAL;

	if (len > mtd->size || pgoff >= (mtd->size >> PAGE_SHIFT))
		return (unsigned long) -EINVAL;

	offset = pgoff << PAGE_SHIFT;
	if (offset > mtd->size - len)
		return (unsigned long) -EINVAL;

	ret = mtd_get_unmapped_area(mtd, len, offset, flags);
	return ret == -EOPNOTSUPP ? -ENODEV : ret;
}