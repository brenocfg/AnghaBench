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
 unsigned long HPTE_R_RPN ; 
 int kvmppc_actual_pgsz (unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long kvmppc_mmu_get_real_addr(unsigned long v, unsigned long r,
			unsigned long ea)
{
	unsigned long ra_mask;

	ra_mask = kvmppc_actual_pgsz(v, r) - 1;
	return (r & HPTE_R_RPN & ~ra_mask) | (ea & ra_mask);
}