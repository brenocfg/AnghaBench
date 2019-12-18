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

/* Variables and functions */
 int FMC2_ECC_BCH8 ; 
 int FMC2_ECC_HAM ; 

__attribute__((used)) static int stm32_fmc2_calc_ecc_bytes(int step_size, int strength)
{
	/* Hamming */
	if (strength == FMC2_ECC_HAM)
		return 4;

	/* BCH8 */
	if (strength == FMC2_ECC_BCH8)
		return 14;

	/* BCH4 */
	return 8;
}