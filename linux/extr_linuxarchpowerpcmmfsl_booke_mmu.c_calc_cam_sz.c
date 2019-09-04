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
typedef  unsigned long phys_addr_t ;

/* Variables and functions */
 int MMUCFG_MAVN ; 
 int MMUCFG_MAVN_V1 ; 
 int /*<<< orphan*/  SPRN_MMUCFG ; 
 int /*<<< orphan*/  SPRN_TLB1CFG ; 
 int /*<<< orphan*/  SPRN_TLB1PS ; 
 unsigned int __ffs (unsigned long) ; 
 int __ilog2 (int) ; 
 int mfspr (int /*<<< orphan*/ ) ; 

unsigned long calc_cam_sz(unsigned long ram, unsigned long virt,
			  phys_addr_t phys)
{
	unsigned int camsize = __ilog2(ram);
	unsigned int align = __ffs(virt | phys);
	unsigned long max_cam;

	if ((mfspr(SPRN_MMUCFG) & MMUCFG_MAVN) == MMUCFG_MAVN_V1) {
		/* Convert (4^max) kB to (2^max) bytes */
		max_cam = ((mfspr(SPRN_TLB1CFG) >> 16) & 0xf) * 2 + 10;
		camsize &= ~1U;
		align &= ~1U;
	} else {
		/* Convert (2^max) kB to (2^max) bytes */
		max_cam = __ilog2(mfspr(SPRN_TLB1PS)) + 10;
	}

	if (camsize > align)
		camsize = align;
	if (camsize > max_cam)
		camsize = max_cam;

	return 1UL << camsize;
}