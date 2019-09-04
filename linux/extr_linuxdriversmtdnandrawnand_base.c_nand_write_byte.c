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
struct nand_chip {int /*<<< orphan*/  (* write_buf ) (struct mtd_info*,int /*<<< orphan*/ *,int) ;} ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void nand_write_byte(struct mtd_info *mtd, uint8_t byte)
{
	struct nand_chip *chip = mtd_to_nand(mtd);

	chip->write_buf(mtd, &byte, 1);
}