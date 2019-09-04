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
struct mtd_info {int dummy; } ;
struct jz4780_nand_chip {int reading; } ;

/* Variables and functions */
 int NAND_ECC_READ ; 
 struct jz4780_nand_chip* to_jz4780_nand_chip (struct mtd_info*) ; 

__attribute__((used)) static void jz4780_nand_ecc_hwctl(struct mtd_info *mtd, int mode)
{
	struct jz4780_nand_chip *nand = to_jz4780_nand_chip(mtd);

	nand->reading = (mode == NAND_ECC_READ);
}