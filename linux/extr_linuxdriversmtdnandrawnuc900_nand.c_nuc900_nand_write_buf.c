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
 int /*<<< orphan*/  write_data_reg (struct nuc900_nand*,unsigned char const) ; 

__attribute__((used)) static void nuc900_nand_write_buf(struct mtd_info *mtd,
				  const unsigned char *buf, int len)
{
	int i;
	struct nuc900_nand *nand = mtd_to_nuc900(mtd);

	for (i = 0; i < len; i++)
		write_data_reg(nand, buf[i]);
}