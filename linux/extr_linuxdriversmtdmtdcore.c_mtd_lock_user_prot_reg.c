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
struct mtd_info {int (* _lock_user_prot_reg ) (struct mtd_info*,int /*<<< orphan*/ ,size_t) ;} ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct mtd_info*,int /*<<< orphan*/ ,size_t) ; 

int mtd_lock_user_prot_reg(struct mtd_info *mtd, loff_t from, size_t len)
{
	if (!mtd->_lock_user_prot_reg)
		return -EOPNOTSUPP;
	if (!len)
		return 0;
	return mtd->_lock_user_prot_reg(mtd, from, len);
}