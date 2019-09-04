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
struct TYPE_2__ {void* addr_hi; void* addr_lo; } ;
union bfi_addr_u {TYPE_1__ a32; } ;
typedef  int /*<<< orphan*/  u64 ;
typedef  void* u32 ;

/* Variables and functions */
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
__bfa_dma_be_addr_set(union bfi_addr_u *dma_addr, u64 pa)
{
	dma_addr->a32.addr_lo = (u32) htonl(pa);
	dma_addr->a32.addr_hi = (u32) htonl(upper_32_bits(pa));
}