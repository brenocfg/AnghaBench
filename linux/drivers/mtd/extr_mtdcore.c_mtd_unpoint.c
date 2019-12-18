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
struct mtd_info {int (* _unpoint ) (struct mtd_info*,scalar_t__,size_t) ;scalar_t__ size; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int stub1 (struct mtd_info*,scalar_t__,size_t) ; 

int mtd_unpoint(struct mtd_info *mtd, loff_t from, size_t len)
{
	if (!mtd->_unpoint)
		return -EOPNOTSUPP;
	if (from < 0 || from >= mtd->size || len > mtd->size - from)
		return -EINVAL;
	if (!len)
		return 0;
	return mtd->_unpoint(mtd, from, len);
}