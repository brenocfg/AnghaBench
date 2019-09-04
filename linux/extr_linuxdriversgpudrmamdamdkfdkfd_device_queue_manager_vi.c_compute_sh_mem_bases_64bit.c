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
typedef  unsigned int uint32_t ;

/* Variables and functions */
 unsigned int SH_MEM_BASES__SHARED_BASE__SHIFT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static uint32_t compute_sh_mem_bases_64bit(unsigned int top_address_nybble)
{
	/* In 64-bit mode, we can only control the top 3 bits of the LDS,
	 * scratch and GPUVM apertures.
	 * The hardware fills in the remaining 59 bits according to the
	 * following pattern:
	 * LDS:		X0000000'00000000 - X0000001'00000000 (4GB)
	 * Scratch:	X0000001'00000000 - X0000002'00000000 (4GB)
	 * GPUVM:	Y0010000'00000000 - Y0020000'00000000 (1TB)
	 *
	 * (where X/Y is the configurable nybble with the low-bit 0)
	 *
	 * LDS and scratch will have the same top nybble programmed in the
	 * top 3 bits of SH_MEM_BASES.PRIVATE_BASE.
	 * GPUVM can have a different top nybble programmed in the
	 * top 3 bits of SH_MEM_BASES.SHARED_BASE.
	 * We don't bother to support different top nybbles
	 * for LDS/Scratch and GPUVM.
	 */

	WARN_ON((top_address_nybble & 1) || top_address_nybble > 0xE ||
		top_address_nybble == 0);

	return top_address_nybble << 12 |
			(top_address_nybble << 12) <<
			SH_MEM_BASES__SHARED_BASE__SHIFT;
}