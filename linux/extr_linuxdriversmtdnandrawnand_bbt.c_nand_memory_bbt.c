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
struct nand_chip {int /*<<< orphan*/  data_buf; } ;
struct nand_bbt_descr {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int create_bbt (struct mtd_info*,int /*<<< orphan*/ ,struct nand_bbt_descr*,int) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 

__attribute__((used)) static inline int nand_memory_bbt(struct mtd_info *mtd, struct nand_bbt_descr *bd)
{
	struct nand_chip *this = mtd_to_nand(mtd);

	return create_bbt(mtd, this->data_buf, bd, -1);
}