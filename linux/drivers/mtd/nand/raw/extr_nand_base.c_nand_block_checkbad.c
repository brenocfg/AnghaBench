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
struct nand_chip {scalar_t__ bbt; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int nand_isbad_bbm (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int nand_isbad_bbt (struct nand_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nand_block_checkbad(struct nand_chip *chip, loff_t ofs, int allowbbt)
{
	/* Return info from the table */
	if (chip->bbt)
		return nand_isbad_bbt(chip, ofs, allowbbt);

	return nand_isbad_bbm(chip, ofs);
}