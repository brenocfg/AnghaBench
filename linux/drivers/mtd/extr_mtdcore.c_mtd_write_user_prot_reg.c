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
struct mtd_info {int (* _write_user_prot_reg ) (struct mtd_info*,int /*<<< orphan*/ ,size_t,size_t*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 int stub1 (struct mtd_info*,int /*<<< orphan*/ ,size_t,size_t*,int /*<<< orphan*/ *) ; 

int mtd_write_user_prot_reg(struct mtd_info *mtd, loff_t to, size_t len,
			    size_t *retlen, u_char *buf)
{
	int ret;

	*retlen = 0;
	if (!mtd->_write_user_prot_reg)
		return -EOPNOTSUPP;
	if (!len)
		return 0;
	ret = mtd->_write_user_prot_reg(mtd, to, len, retlen, buf);
	if (ret)
		return ret;

	/*
	 * If no data could be written at all, we are out of memory and
	 * must return -ENOSPC.
	 */
	return (*retlen) ? 0 : -ENOSPC;
}