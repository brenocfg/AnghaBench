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
struct oxnas_nand_ctrl {int /*<<< orphan*/  io_base; } ;
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread8_rep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct oxnas_nand_ctrl* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static void oxnas_nand_read_buf(struct mtd_info *mtd, u8 *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct oxnas_nand_ctrl *oxnas = nand_get_controller_data(chip);

	ioread8_rep(oxnas->io_base, buf, len);
}