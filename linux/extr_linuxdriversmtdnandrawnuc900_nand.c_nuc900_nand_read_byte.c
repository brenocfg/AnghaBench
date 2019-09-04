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
struct nuc900_nand {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 struct nuc900_nand* mtd_to_nuc900 (struct mtd_info*) ; 
 scalar_t__ read_data_reg (struct nuc900_nand*) ; 

__attribute__((used)) static unsigned char nuc900_nand_read_byte(struct mtd_info *mtd)
{
	unsigned char ret;
	struct nuc900_nand *nand = mtd_to_nuc900(mtd);

	ret = (unsigned char)read_data_reg(nand);

	return ret;
}