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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nand_chip {scalar_t__ oob_poi; } ;
struct mtd_info {int writesize; } ;
struct brcmnand_host {int /*<<< orphan*/  last_addr; } ;

/* Variables and functions */
 int FC_SHIFT ; 
 int brcmnand_read (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmnand_set_ecc_enabled (struct brcmnand_host*,int) ; 
 struct brcmnand_host* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int brcmnand_read_page_raw(struct nand_chip *chip, uint8_t *buf,
				  int oob_required, int page)
{
	struct brcmnand_host *host = nand_get_controller_data(chip);
	struct mtd_info *mtd = nand_to_mtd(chip);
	u8 *oob = oob_required ? (u8 *)chip->oob_poi : NULL;
	int ret;

	nand_read_page_op(chip, page, 0, NULL, 0);

	brcmnand_set_ecc_enabled(host, 0);
	ret = brcmnand_read(mtd, chip, host->last_addr,
			mtd->writesize >> FC_SHIFT, (u32 *)buf, oob);
	brcmnand_set_ecc_enabled(host, 1);
	return ret;
}