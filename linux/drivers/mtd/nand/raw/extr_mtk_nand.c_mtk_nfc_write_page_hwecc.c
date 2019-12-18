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
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int mtk_nfc_write_page (int /*<<< orphan*/ ,struct nand_chip*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int mtk_nfc_write_page_hwecc(struct nand_chip *chip, const u8 *buf,
				    int oob_on, int page)
{
	return mtk_nfc_write_page(nand_to_mtd(chip), chip, buf, page, 0);
}