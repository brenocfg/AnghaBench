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
typedef  int u8 ;
struct TYPE_4__ {int len; int* data; } ;
struct TYPE_3__ {int /*<<< orphan*/  onfi; } ;
struct nand_chip {int bits_per_cell; int ecc_strength_ds; TYPE_2__ id; TYPE_1__ parameters; } ;
typedef  int /*<<< orphan*/  id ;

/* Variables and functions */
 int MICRON_ID_ECC_ENABLED ; 
 int MICRON_ID_INTERNAL_ECC_MASK ; 
 int MICRON_ON_DIE_MANDATORY ; 
 int MICRON_ON_DIE_SUPPORTED ; 
 int MICRON_ON_DIE_UNSUPPORTED ; 
 int micron_nand_on_die_ecc_setup (struct nand_chip*,int) ; 
 int nand_readid_op (struct nand_chip*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int micron_supports_on_die_ecc(struct nand_chip *chip)
{
	u8 id[5];
	int ret;

	if (!chip->parameters.onfi)
		return MICRON_ON_DIE_UNSUPPORTED;

	if (chip->bits_per_cell != 1)
		return MICRON_ON_DIE_UNSUPPORTED;

	/*
	 * We only support on-die ECC of 4/512 or 8/512
	 */
	if  (chip->ecc_strength_ds != 4 && chip->ecc_strength_ds != 8)
		return MICRON_ON_DIE_UNSUPPORTED;

	/* 0x2 means on-die ECC is available. */
	if (chip->id.len != 5 ||
	    (chip->id.data[4] & MICRON_ID_INTERNAL_ECC_MASK) != 0x2)
		return MICRON_ON_DIE_UNSUPPORTED;

	ret = micron_nand_on_die_ecc_setup(chip, true);
	if (ret)
		return MICRON_ON_DIE_UNSUPPORTED;

	ret = nand_readid_op(chip, 0, id, sizeof(id));
	if (ret)
		return MICRON_ON_DIE_UNSUPPORTED;

	if (!(id[4] & MICRON_ID_ECC_ENABLED))
		return MICRON_ON_DIE_UNSUPPORTED;

	ret = micron_nand_on_die_ecc_setup(chip, false);
	if (ret)
		return MICRON_ON_DIE_UNSUPPORTED;

	ret = nand_readid_op(chip, 0, id, sizeof(id));
	if (ret)
		return MICRON_ON_DIE_UNSUPPORTED;

	if (id[4] & MICRON_ID_ECC_ENABLED)
		return MICRON_ON_DIE_MANDATORY;

	/*
	 * We only support on-die ECC of 4/512 or 8/512
	 */
	if  (chip->ecc_strength_ds != 4 && chip->ecc_strength_ds != 8)
		return MICRON_ON_DIE_UNSUPPORTED;

	return MICRON_ON_DIE_SUPPORTED;
}