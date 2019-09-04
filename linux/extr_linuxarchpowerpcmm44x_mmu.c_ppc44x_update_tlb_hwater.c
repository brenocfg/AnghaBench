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
 int /*<<< orphan*/  flush_icache_range (unsigned long,unsigned long) ; 
 unsigned int tlb_44x_hwater ; 

__attribute__((used)) static void ppc44x_update_tlb_hwater(void)
{
	extern unsigned int tlb_44x_patch_hwater_D[];
	extern unsigned int tlb_44x_patch_hwater_I[];

	/* The TLB miss handlers hard codes the watermark in a cmpli
	 * instruction to improve performances rather than loading it
	 * from the global variable. Thus, we patch the instructions
	 * in the 2 TLB miss handlers when updating the value
	 */
	tlb_44x_patch_hwater_D[0] = (tlb_44x_patch_hwater_D[0] & 0xffff0000) |
		tlb_44x_hwater;
	flush_icache_range((unsigned long)&tlb_44x_patch_hwater_D[0],
			   (unsigned long)&tlb_44x_patch_hwater_D[1]);
	tlb_44x_patch_hwater_I[0] = (tlb_44x_patch_hwater_I[0] & 0xffff0000) |
		tlb_44x_hwater;
	flush_icache_range((unsigned long)&tlb_44x_patch_hwater_I[0],
			   (unsigned long)&tlb_44x_patch_hwater_I[1]);
}