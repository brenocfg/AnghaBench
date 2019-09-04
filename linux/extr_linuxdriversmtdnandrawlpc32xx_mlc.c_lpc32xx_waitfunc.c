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
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int NAND_STATUS_READY ; 
 int /*<<< orphan*/  lpc32xx_waitfunc_controller (struct mtd_info*,struct nand_chip*) ; 
 int /*<<< orphan*/  lpc32xx_waitfunc_nand (struct mtd_info*,struct nand_chip*) ; 

__attribute__((used)) static int lpc32xx_waitfunc(struct mtd_info *mtd, struct nand_chip *chip)
{
	lpc32xx_waitfunc_nand(mtd, chip);
	lpc32xx_waitfunc_controller(mtd, chip);

	return NAND_STATUS_READY;
}