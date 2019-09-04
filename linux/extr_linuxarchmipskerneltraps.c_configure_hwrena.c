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
 int MIPS_HWRENA_CC ; 
 int MIPS_HWRENA_CCRES ; 
 int MIPS_HWRENA_CPUNUM ; 
 int MIPS_HWRENA_SYNCISTEP ; 
 int MIPS_HWRENA_ULR ; 
 scalar_t__ cpu_has_mips_r2_r6 ; 
 scalar_t__ cpu_has_userlocal ; 
 int cpu_hwrena_impl_bits ; 
 int hwrena ; 
 int /*<<< orphan*/  noulri ; 
 int /*<<< orphan*/  write_c0_hwrena (int) ; 

__attribute__((used)) static void configure_hwrena(void)
{
	hwrena = cpu_hwrena_impl_bits;

	if (cpu_has_mips_r2_r6)
		hwrena |= MIPS_HWRENA_CPUNUM |
			  MIPS_HWRENA_SYNCISTEP |
			  MIPS_HWRENA_CC |
			  MIPS_HWRENA_CCRES;

	if (!noulri && cpu_has_userlocal)
		hwrena |= MIPS_HWRENA_ULR;

	if (hwrena)
		write_c0_hwrena(hwrena);
}