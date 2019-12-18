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
struct TYPE_2__ {unsigned char bas_hi; unsigned char bas_md; unsigned char bas_lo; } ;

/* Variables and functions */
 unsigned long atari_stram_to_phys (void*) ; 
 TYPE_1__ shifter_st ; 

__attribute__((used)) static void set_screen_base(void *s_base)
{
	unsigned long addr;

	addr = atari_stram_to_phys(s_base);
	/* Setup Screen Memory */
	shifter_st.bas_hi = (unsigned char)((addr & 0xff0000) >> 16);
	shifter_st.bas_md = (unsigned char)((addr & 0x00ff00) >> 8);
	shifter_st.bas_lo = (unsigned char)(addr & 0x0000ff);
}