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
struct mtd_info {int erasesize; } ;
typedef  int loff_t ;

/* Variables and functions */
 int mtd_block_isbad (struct mtd_info*,int) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 

__attribute__((used)) static int is_block_bad(struct mtd_info *mtd, unsigned int ebnum)
{
	int ret;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	ret = mtd_block_isbad(mtd, addr);
	if (ret)
		pr_info("block %d is bad\n", ebnum);

	return ret;
}