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
typedef  size_t u8 ;
typedef  int u32 ;
struct fsl_re_cmpnd_frame {int efrl32; int /*<<< orphan*/  addr_low; int /*<<< orphan*/  addr_high; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int FSL_RE_CF_FINAL_SHIFT ; 
 size_t FSL_RE_CF_LENGTH_MASK ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fill_cfd_frame(struct fsl_re_cmpnd_frame *cf, u8 index,
			   size_t length, dma_addr_t addr, bool final)
{
	u32 efrl = length & FSL_RE_CF_LENGTH_MASK;

	efrl |= final << FSL_RE_CF_FINAL_SHIFT;
	cf[index].efrl32 = efrl;
	cf[index].addr_high = upper_32_bits(addr);
	cf[index].addr_low = lower_32_bits(addr);
}