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
typedef  scalar_t__ u32 ;
struct sharpsl_ftl {unsigned int logmax; unsigned int* log2phy; } ;
struct mtd_info {int erasesize; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 unsigned int mtd_div_by_eb (scalar_t__,struct mtd_info*) ; 
 scalar_t__ mtd_is_bitflip (int) ; 
 int mtd_mod_by_eb (scalar_t__,struct mtd_info*) ; 
 int mtd_read (struct mtd_info*,int,size_t,size_t*,void*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int sharpsl_nand_read_laddr(struct mtd_info *mtd,
				   loff_t from,
				   size_t len,
				   void *buf,
				   struct sharpsl_ftl *ftl)
{
	unsigned int log_num, final_log_num;
	unsigned int block_num;
	loff_t block_adr;
	loff_t block_ofs;
	size_t retlen;
	int err;

	log_num = mtd_div_by_eb((u32)from, mtd);
	final_log_num = mtd_div_by_eb(((u32)from + len - 1), mtd);

	if (len <= 0 || log_num >= ftl->logmax || final_log_num > log_num)
		return -EINVAL;

	block_num = ftl->log2phy[log_num];
	block_adr = (loff_t)block_num * mtd->erasesize;
	block_ofs = mtd_mod_by_eb((u32)from, mtd);

	err = mtd_read(mtd, block_adr + block_ofs, len, &retlen, buf);
	/* Ignore corrected ECC errors */
	if (mtd_is_bitflip(err))
		err = 0;

	if (!err && retlen != len)
		err = -EIO;

	if (err)
		pr_err("sharpslpart: error, read failed at %#llx\n",
		       block_adr + block_ofs);

	return err;
}