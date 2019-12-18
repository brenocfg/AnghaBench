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
typedef  int /*<<< orphan*/  u_char ;
struct mtd_info {int (* _panic_write ) (struct mtd_info*,scalar_t__,size_t,size_t*,int /*<<< orphan*/  const*) ;scalar_t__ size; int flags; int oops_panic_write; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EROFS ; 
 int MTD_WRITEABLE ; 
 int stub1 (struct mtd_info*,scalar_t__,size_t,size_t*,int /*<<< orphan*/  const*) ; 

int mtd_panic_write(struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen,
		    const u_char *buf)
{
	*retlen = 0;
	if (!mtd->_panic_write)
		return -EOPNOTSUPP;
	if (to < 0 || to >= mtd->size || len > mtd->size - to)
		return -EINVAL;
	if (!(mtd->flags & MTD_WRITEABLE))
		return -EROFS;
	if (!len)
		return 0;
	if (!mtd->oops_panic_write)
		mtd->oops_panic_write = true;

	return mtd->_panic_write(mtd, to, len, retlen, buf);
}