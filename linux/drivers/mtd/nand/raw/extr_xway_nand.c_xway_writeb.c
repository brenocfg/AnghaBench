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
struct xway_nand_data {scalar_t__ nandaddr; } ;
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct xway_nand_data* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void xway_writeb(struct mtd_info *mtd, int op, u8 value)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct xway_nand_data *data = nand_get_controller_data(chip);

	writeb(value, data->nandaddr + op);
}