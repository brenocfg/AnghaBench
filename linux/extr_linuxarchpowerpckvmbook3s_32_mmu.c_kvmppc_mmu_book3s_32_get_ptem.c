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
typedef  int gva_t ;

/* Variables and functions */
 int sr_vsid (int) ; 

__attribute__((used)) static u32 kvmppc_mmu_book3s_32_get_ptem(u32 sre, gva_t eaddr, bool primary)
{
	return ((eaddr & 0x0fffffff) >> 22) | (sr_vsid(sre) << 7) |
	       (primary ? 0 : 0x40) | 0x80000000;
}