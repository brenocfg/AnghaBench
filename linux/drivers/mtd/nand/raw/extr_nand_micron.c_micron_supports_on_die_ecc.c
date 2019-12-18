#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_7__ {int strength; } ;
struct TYPE_8__ {TYPE_3__ eccreq; } ;
struct TYPE_6__ {int len; int* data; } ;
struct TYPE_5__ {int /*<<< orphan*/  onfi; } ;
struct nand_chip {TYPE_4__ base; TYPE_2__ id; TYPE_1__ parameters; } ;
typedef  int /*<<< orphan*/  id ;

/* Variables and functions */
 int MICRON_ID_ECC_ENABLED ; 
 int MICRON_ID_INTERNAL_ECC_MASK ; 
 int MICRON_ON_DIE_MANDATORY ; 
 int MICRON_ON_DIE_SUPPORTED ; 
 int MICRON_ON_DIE_UNSUPPORTED ; 
 int micron_nand_on_die_ecc_setup (struct nand_chip*,int) ; 
 int nand_readid_op (struct nand_chip*,int /*<<< orphan*/ ,int*,int) ; 
 int nanddev_bits_per_cell (TYPE_4__*) ; 

__attribute__((used)) static int micron_supports_on_die_ecc(struct nand_chip *chip)
{
	u8 id[5];
	int ret;

	if (!chip->parameters.onfi)
		return MICRON_ON_DIE_UNSUPPORTED;

	if (nanddev_bits_per_cell(&chip->base) != 1)
		return MICRON_ON_DIE_UNSUPPORTED;

	/*
	 * We only support on-die ECC of 4/512 or 8/512
	 */
	if  (chip->base.eccreq.strength != 4 && chip->base.eccreq.strength != 8)
		return MICRON_ON_DIE_UNSUPPORTED;

	/* 0x2 means on-die ECC is available. */
	if (chip->id.len != 5 ||
	    (chip->id.data[4] & MICRON_ID_INTERNAL_ECC_MASK) != 0x2)
		return MICRON_ON_DIE_UNSUPPORTED;

	/*
	 * It seems that there are devices which do not support ECC officially.
	 * At least the MT29F2G08ABAGA / MT29F2G08ABBGA devices supports
	 * enabling the ECC feature but don't reflect that to the READ_ID table.
	 * So we have to guarantee that we disable the ECC feature directly
	 * after we did the READ_ID table command. Later we can evaluate the
	 * ECC_ENABLE support.
	 */
	ret = micron_nand_on_die_ecc_setup(chip, true);
	if (ret)
		return MICRON_ON_DIE_UNSUPPORTED;

	ret = nand_readid_op(chip, 0, id, sizeof(id));
	if (ret)
		return MICRON_ON_DIE_UNSUPPORTED;

	ret = micron_nand_on_die_ecc_setup(chip, false);
	if (ret)
		return MICRON_ON_DIE_UNSUPPORTED;

	if (!(id[4] & MICRON_ID_ECC_ENABLED))
		return MICRON_ON_DIE_UNSUPPORTED;

	ret = nand_readid_op(chip, 0, id, sizeof(id));
	if (ret)
		return MICRON_ON_DIE_UNSUPPORTED;

	if (id[4] & MICRON_ID_ECC_ENABLED)
		return MICRON_ON_DIE_MANDATORY;

	/*
	 * We only support on-die ECC of 4/512 or 8/512
	 */
	if  (chip->base.eccreq.strength != 4 && chip->base.eccreq.strength != 8)
		return MICRON_ON_DIE_UNSUPPORTED;

	return MICRON_ON_DIE_SUPPORTED;
}