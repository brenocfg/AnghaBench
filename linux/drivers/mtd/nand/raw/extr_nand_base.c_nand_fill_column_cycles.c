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
typedef  unsigned int u8 ;
struct nand_chip {int options; } ;
struct mtd_info {unsigned int writesize; unsigned int oobsize; } ;

/* Variables and functions */
 int EINVAL ; 
 int NAND_BUSWIDTH_16 ; 
 scalar_t__ WARN_ON (unsigned int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int nand_fill_column_cycles(struct nand_chip *chip, u8 *addrs,
				   unsigned int offset_in_page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	/* Make sure the offset is less than the actual page size. */
	if (offset_in_page > mtd->writesize + mtd->oobsize)
		return -EINVAL;

	/*
	 * On small page NANDs, there's a dedicated command to access the OOB
	 * area, and the column address is relative to the start of the OOB
	 * area, not the start of the page. Asjust the address accordingly.
	 */
	if (mtd->writesize <= 512 && offset_in_page >= mtd->writesize)
		offset_in_page -= mtd->writesize;

	/*
	 * The offset in page is expressed in bytes, if the NAND bus is 16-bit
	 * wide, then it must be divided by 2.
	 */
	if (chip->options & NAND_BUSWIDTH_16) {
		if (WARN_ON(offset_in_page % 2))
			return -EINVAL;

		offset_in_page /= 2;
	}

	addrs[0] = offset_in_page;

	/*
	 * Small page NANDs use 1 cycle for the columns, while large page NANDs
	 * need 2
	 */
	if (mtd->writesize <= 512)
		return 1;

	addrs[1] = offset_in_page >> 8;

	return 2;
}