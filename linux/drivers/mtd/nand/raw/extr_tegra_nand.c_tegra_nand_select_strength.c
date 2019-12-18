#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int algo; } ;
struct nand_chip {int options; TYPE_1__ ecc; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int BITS_PER_STEP_BCH ; 
 int BITS_PER_STEP_RS ; 
 int EINVAL ; 
#define  NAND_ECC_BCH 129 
#define  NAND_ECC_RS 128 
 int NAND_IS_BOOT_MEDIUM ; 
 int* bch_strength ; 
 int* bch_strength_bootable ; 
 int* rs_strength ; 
 int* rs_strength_bootable ; 
 int tegra_nand_get_strength (struct nand_chip*,int const*,int,int,int) ; 

__attribute__((used)) static int tegra_nand_select_strength(struct nand_chip *chip, int oobsize)
{
	const int *strength;
	int strength_len, bits_per_step;

	switch (chip->ecc.algo) {
	case NAND_ECC_RS:
		bits_per_step = BITS_PER_STEP_RS;
		if (chip->options & NAND_IS_BOOT_MEDIUM) {
			strength = rs_strength_bootable;
			strength_len = ARRAY_SIZE(rs_strength_bootable);
		} else {
			strength = rs_strength;
			strength_len = ARRAY_SIZE(rs_strength);
		}
		break;
	case NAND_ECC_BCH:
		bits_per_step = BITS_PER_STEP_BCH;
		if (chip->options & NAND_IS_BOOT_MEDIUM) {
			strength = bch_strength_bootable;
			strength_len = ARRAY_SIZE(bch_strength_bootable);
		} else {
			strength = bch_strength;
			strength_len = ARRAY_SIZE(bch_strength);
		}
		break;
	default:
		return -EINVAL;
	}

	return tegra_nand_get_strength(chip, strength, strength_len,
				       bits_per_step, oobsize);
}