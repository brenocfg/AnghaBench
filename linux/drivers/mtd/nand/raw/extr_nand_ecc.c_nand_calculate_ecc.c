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
struct TYPE_2__ {int options; int /*<<< orphan*/  size; } ;
struct nand_chip {TYPE_1__ ecc; } ;

/* Variables and functions */
 int NAND_ECC_SOFT_HAMMING_SM_ORDER ; 
 int /*<<< orphan*/  __nand_calculate_ecc (unsigned char const*,int /*<<< orphan*/ ,unsigned char*,int) ; 

int nand_calculate_ecc(struct nand_chip *chip, const unsigned char *buf,
		       unsigned char *code)
{
	bool sm_order = chip->ecc.options & NAND_ECC_SOFT_HAMMING_SM_ORDER;

	__nand_calculate_ecc(buf, chip->ecc.size, code, sm_order);

	return 0;
}