#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  steps; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sunxi_nfc_hw_ecc_read_chunks_dma (struct mtd_info*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int sunxi_nfc_hw_ecc_read_page (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int sunxi_nfc_hw_ecc_read_page_dma(struct mtd_info *mtd,
					  struct nand_chip *chip, u8 *buf,
					  int oob_required, int page)
{
	int ret;

	nand_read_page_op(chip, page, 0, NULL, 0);

	ret = sunxi_nfc_hw_ecc_read_chunks_dma(mtd, buf, oob_required, page,
					       chip->ecc.steps);
	if (ret >= 0)
		return ret;

	/* Fallback to PIO mode */
	return sunxi_nfc_hw_ecc_read_page(mtd, chip, buf, oob_required, page);
}