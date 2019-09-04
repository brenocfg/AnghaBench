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
struct mtd_info {int (* _point ) (struct mtd_info*,scalar_t__,size_t,size_t*,void**,scalar_t__*) ;scalar_t__ size; } ;
typedef  scalar_t__ resource_size_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int stub1 (struct mtd_info*,scalar_t__,size_t,size_t*,void**,scalar_t__*) ; 

int mtd_point(struct mtd_info *mtd, loff_t from, size_t len, size_t *retlen,
	      void **virt, resource_size_t *phys)
{
	*retlen = 0;
	*virt = NULL;
	if (phys)
		*phys = 0;
	if (!mtd->_point)
		return -EOPNOTSUPP;
	if (from < 0 || from >= mtd->size || len > mtd->size - from)
		return -EINVAL;
	if (!len)
		return 0;
	return mtd->_point(mtd, from, len, retlen, virt, phys);
}