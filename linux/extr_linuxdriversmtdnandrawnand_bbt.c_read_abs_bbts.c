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
typedef  void* uint8_t ;
struct nand_chip {int page_shift; } ;
struct nand_bbt_descr {int options; void** version; scalar_t__* pages; } ;
struct mtd_info {int /*<<< orphan*/  writesize; } ;
typedef  int loff_t ;

/* Variables and functions */
 int NAND_BBT_VERSION ; 
 size_t bbt_get_ver_offs (struct mtd_info*,struct nand_bbt_descr*) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__,void*) ; 
 int /*<<< orphan*/  scan_read (struct mtd_info*,void**,int,int /*<<< orphan*/ ,struct nand_bbt_descr*) ; 

__attribute__((used)) static void read_abs_bbts(struct mtd_info *mtd, uint8_t *buf,
			  struct nand_bbt_descr *td, struct nand_bbt_descr *md)
{
	struct nand_chip *this = mtd_to_nand(mtd);

	/* Read the primary version, if available */
	if (td->options & NAND_BBT_VERSION) {
		scan_read(mtd, buf, (loff_t)td->pages[0] << this->page_shift,
			      mtd->writesize, td);
		td->version[0] = buf[bbt_get_ver_offs(mtd, td)];
		pr_info("Bad block table at page %d, version 0x%02X\n",
			 td->pages[0], td->version[0]);
	}

	/* Read the mirror version, if available */
	if (md && (md->options & NAND_BBT_VERSION)) {
		scan_read(mtd, buf, (loff_t)md->pages[0] << this->page_shift,
			      mtd->writesize, md);
		md->version[0] = buf[bbt_get_ver_offs(mtd, md)];
		pr_info("Bad block table at page %d, version 0x%02X\n",
			 md->pages[0], md->version[0]);
	}
}