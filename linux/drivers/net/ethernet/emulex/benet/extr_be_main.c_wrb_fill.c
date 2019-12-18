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
typedef  int /*<<< orphan*/  u64 ;
struct be_eth_wrb {scalar_t__ rsvd0; void* frag_len; void* frag_pa_lo; void* frag_pa_hi; } ;

/* Variables and functions */
 int ETH_WRB_FRAG_LEN_MASK ; 
 void* cpu_to_le32 (int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void wrb_fill(struct be_eth_wrb *wrb, u64 addr, int len)
{
	wrb->frag_pa_hi = cpu_to_le32(upper_32_bits(addr));
	wrb->frag_pa_lo = cpu_to_le32(lower_32_bits(addr));
	wrb->frag_len = cpu_to_le32(len & ETH_WRB_FRAG_LEN_MASK);
	wrb->rsvd0 = 0;
}