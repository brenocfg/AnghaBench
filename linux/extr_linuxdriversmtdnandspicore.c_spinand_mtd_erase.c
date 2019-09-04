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
struct spinand_device {int /*<<< orphan*/  lock; } ;
struct mtd_info {int dummy; } ;
struct erase_info {int dummy; } ;

/* Variables and functions */
 struct spinand_device* mtd_to_spinand (struct mtd_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nanddev_mtd_erase (struct mtd_info*,struct erase_info*) ; 

__attribute__((used)) static int spinand_mtd_erase(struct mtd_info *mtd,
			     struct erase_info *einfo)
{
	struct spinand_device *spinand = mtd_to_spinand(mtd);
	int ret;

	mutex_lock(&spinand->lock);
	ret = nanddev_mtd_erase(mtd, einfo);
	mutex_unlock(&spinand->lock);

	return ret;
}