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
struct sm_oob {int /*<<< orphan*/  ecc2; int /*<<< orphan*/  ecc1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MTD_NAND_ECC_SW_HAMMING_SMC ; 
 int EIO ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_SMALL_PAGE ; 
 int /*<<< orphan*/  __nand_calculate_ecc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ __nand_correct_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sm_correct_sector(uint8_t *buffer, struct sm_oob *oob)
{
	uint8_t ecc[3];

	__nand_calculate_ecc(buffer, SM_SMALL_PAGE, ecc,
			     IS_ENABLED(CONFIG_MTD_NAND_ECC_SW_HAMMING_SMC));
	if (__nand_correct_data(buffer, ecc, oob->ecc1, SM_SMALL_PAGE,
				IS_ENABLED(CONFIG_MTD_NAND_ECC_SW_HAMMING_SMC)) < 0)
		return -EIO;

	buffer += SM_SMALL_PAGE;

	__nand_calculate_ecc(buffer, SM_SMALL_PAGE, ecc,
			     IS_ENABLED(CONFIG_MTD_NAND_ECC_SW_HAMMING_SMC));
	if (__nand_correct_data(buffer, ecc, oob->ecc2, SM_SMALL_PAGE,
				IS_ENABLED(CONFIG_MTD_NAND_ECC_SW_HAMMING_SMC)) < 0)
		return -EIO;
	return 0;
}