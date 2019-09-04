#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mtd_info {int dummy; } ;
struct jz4780_nand_controller {int /*<<< orphan*/  bch; } ;
struct TYPE_4__ {int /*<<< orphan*/  strength; int /*<<< orphan*/  bytes; int /*<<< orphan*/  size; } ;
struct TYPE_3__ {TYPE_2__ ecc; int /*<<< orphan*/  controller; } ;
struct jz4780_nand_chip {TYPE_1__ chip; } ;
struct jz4780_bch_params {int /*<<< orphan*/  strength; int /*<<< orphan*/  bytes; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int jz4780_bch_correct (int /*<<< orphan*/ ,struct jz4780_bch_params*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct jz4780_nand_chip* to_jz4780_nand_chip (struct mtd_info*) ; 
 struct jz4780_nand_controller* to_jz4780_nand_controller (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jz4780_nand_ecc_correct(struct mtd_info *mtd, u8 *dat,
				   u8 *read_ecc, u8 *calc_ecc)
{
	struct jz4780_nand_chip *nand = to_jz4780_nand_chip(mtd);
	struct jz4780_nand_controller *nfc = to_jz4780_nand_controller(nand->chip.controller);
	struct jz4780_bch_params params;

	params.size = nand->chip.ecc.size;
	params.bytes = nand->chip.ecc.bytes;
	params.strength = nand->chip.ecc.strength;

	return jz4780_bch_correct(nfc->bch, &params, dat, read_ecc);
}