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
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int gpmi_ecc_read_page_data (struct nand_chip*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpmi_ecc_read_page(struct mtd_info *mtd, struct nand_chip *chip,
			      uint8_t *buf, int oob_required, int page)
{
	nand_read_page_op(chip, page, 0, NULL, 0);

	return gpmi_ecc_read_page_data(chip, buf, oob_required, page);
}