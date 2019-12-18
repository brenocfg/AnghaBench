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
typedef  int /*<<< orphan*/  u32 ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; } ;
struct mtd_info {int dummy; } ;
struct brcmnand_host {int /*<<< orphan*/  last_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmnand_write (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*) ; 
 struct brcmnand_host* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_prog_page_begin_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nand_prog_page_end_op (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int brcmnand_write_page(struct nand_chip *chip, const uint8_t *buf,
			       int oob_required, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct brcmnand_host *host = nand_get_controller_data(chip);
	void *oob = oob_required ? chip->oob_poi : NULL;

	nand_prog_page_begin_op(chip, page, 0, NULL, 0);
	brcmnand_write(mtd, chip, host->last_addr, (const u32 *)buf, oob);

	return nand_prog_page_end_op(chip);
}