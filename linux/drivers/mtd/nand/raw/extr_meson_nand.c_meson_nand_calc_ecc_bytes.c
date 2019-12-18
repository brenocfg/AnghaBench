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
 int ALIGN (int,int) ; 
 int DIV_ROUND_UP (int,int) ; 
 int ECC_PARITY_BCH8_512B ; 
 int fls (int) ; 

__attribute__((used)) static int meson_nand_calc_ecc_bytes(int step_size, int strength)
{
	int ecc_bytes;

	if (step_size == 512 && strength == 8)
		return ECC_PARITY_BCH8_512B;

	ecc_bytes = DIV_ROUND_UP(strength * fls(step_size * 8), 8);
	ecc_bytes = ALIGN(ecc_bytes, 2);

	return ecc_bytes;
}