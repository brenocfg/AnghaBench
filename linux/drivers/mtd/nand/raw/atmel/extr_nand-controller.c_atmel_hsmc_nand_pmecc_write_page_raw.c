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
 int atmel_hsmc_nand_pmecc_write_pg (struct nand_chip*,int /*<<< orphan*/  const*,int,int,int) ; 

__attribute__((used)) static int atmel_hsmc_nand_pmecc_write_page_raw(struct nand_chip *chip,
						const u8 *buf,
						int oob_required, int page)
{
	return atmel_hsmc_nand_pmecc_write_pg(chip, buf, oob_required, page,
					      true);
}