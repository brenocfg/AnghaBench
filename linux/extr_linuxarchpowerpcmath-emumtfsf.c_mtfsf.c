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
typedef  int u32 ;

/* Variables and functions */
 int FPSCR_FEX ; 
 int FPSCR_VX ; 
 int FPSCR_VXCVI ; 
 int FPSCR_VXIDI ; 
 int FPSCR_VXIMZ ; 
 int FPSCR_VXISI ; 
 int FPSCR_VXSNAN ; 
 int FPSCR_VXSOFT ; 
 int FPSCR_VXSQRT ; 
 int FPSCR_VXVC ; 
 int FPSCR_VXZDZ ; 
 int __FPU_FPSCR ; 
 scalar_t__ likely (int) ; 

int
mtfsf(unsigned int FM, u32 *frB)
{
	u32 mask;
	u32 fpscr;

	if (likely(FM == 1))
		mask = 0x0f;
	else if (likely(FM == 0xff))
		mask = ~0;
	else {
		mask = ((FM & 1) |
				((FM << 3) & 0x10) |
				((FM << 6) & 0x100) |
				((FM << 9) & 0x1000) |
				((FM << 12) & 0x10000) |
				((FM << 15) & 0x100000) |
				((FM << 18) & 0x1000000) |
				((FM << 21) & 0x10000000)) * 15;
	}

	fpscr = ((__FPU_FPSCR & ~mask) | (frB[1] & mask)) &
		~(FPSCR_VX | FPSCR_FEX | 0x800);

	if (fpscr & (FPSCR_VXSNAN | FPSCR_VXISI | FPSCR_VXIDI |
		     FPSCR_VXZDZ | FPSCR_VXIMZ | FPSCR_VXVC |
		     FPSCR_VXSOFT | FPSCR_VXSQRT | FPSCR_VXCVI))
		fpscr |= FPSCR_VX;

	/* The bit order of exception enables and exception status
	 * is the same. Simply shift and mask to check for enabled
	 * exceptions.
	 */
	if (fpscr & (fpscr >> 22) &  0xf8)
		fpscr |= FPSCR_FEX;

	__FPU_FPSCR = fpscr;

#ifdef DEBUG
	printk("%s: %02x %p: %08lx\n", __func__, FM, frB, __FPU_FPSCR);
#endif

	return 0;
}