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
typedef  scalar_t__ uint64_t ;
struct mtd_info {scalar_t__ erasesize; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ mtd_block_isbad (struct mtd_info*,scalar_t__) ; 
 scalar_t__ mtd_can_have_bb (struct mtd_info*) ; 

__attribute__((used)) static unsigned int mtdswap_badblocks(struct mtd_info *mtd, uint64_t size)
{
	loff_t offset;
	unsigned int badcnt;

	badcnt = 0;

	if (mtd_can_have_bb(mtd))
		for (offset = 0; offset < size; offset += mtd->erasesize)
			if (mtd_block_isbad(mtd, offset))
				badcnt++;

	return badcnt;
}