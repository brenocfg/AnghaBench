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
struct mtd_info {int /*<<< orphan*/  writesize; } ;
struct denali_nand_info {int dummy; } ;

/* Variables and functions */
 int denali_data_xfer (struct denali_nand_info*,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct denali_nand_info* mtd_to_denali (struct mtd_info*) ; 

__attribute__((used)) static int denali_write_page(struct mtd_info *mtd, struct nand_chip *chip,
			     const uint8_t *buf, int oob_required, int page)
{
	struct denali_nand_info *denali = mtd_to_denali(mtd);

	return denali_data_xfer(denali, (void *)buf, mtd->writesize,
				page, 0, 1);
}