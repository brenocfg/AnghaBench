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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nand_chip {int dummy; } ;
struct mtk_nfc {int /*<<< orphan*/  buffer; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int mtk_nfc_format_subpage (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int mtk_nfc_write_page (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/ ,int,int) ; 
 struct mtk_nfc* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int mtk_nfc_write_subpage_hwecc(struct nand_chip *chip, u32 offset,
				       u32 data_len, const u8 *buf,
				       int oob_on, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct mtk_nfc *nfc = nand_get_controller_data(chip);
	int ret;

	ret = mtk_nfc_format_subpage(mtd, offset, data_len, buf);
	if (ret < 0)
		return ret;

	/* use the data in the private buffer (now with FDM and CRC) */
	return mtk_nfc_write_page(mtd, chip, nfc->buffer, page, 1);
}