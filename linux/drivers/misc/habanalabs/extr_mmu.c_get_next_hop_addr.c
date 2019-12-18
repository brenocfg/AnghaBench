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
typedef  int u64 ;
struct hl_ctx {int dummy; } ;

/* Variables and functions */
 int PAGE_PRESENT_MASK ; 
 int PHYS_ADDR_MASK ; 
 int ULLONG_MAX ; 

__attribute__((used)) static inline u64 get_next_hop_addr(struct hl_ctx *ctx, u64 curr_pte)
{
	if (curr_pte & PAGE_PRESENT_MASK)
		return curr_pte & PHYS_ADDR_MASK;
	else
		return ULLONG_MAX;
}