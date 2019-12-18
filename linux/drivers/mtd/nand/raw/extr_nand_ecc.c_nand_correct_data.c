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
 int __nand_correct_data (unsigned char*,unsigned char*,unsigned char*,int /*<<< orphan*/ ,int) ; 

int nand_correct_data(struct nand_chip *chip, unsigned char *buf,
		      unsigned char *read_ecc, unsigned char *calc_ecc)
{
	bool sm_order = chip->ecc.options & NAND_ECC_SOFT_HAMMING_SM_ORDER;

	return __nand_correct_data(buf, read_ecc, calc_ecc, chip->ecc.size,
				   sm_order);
}