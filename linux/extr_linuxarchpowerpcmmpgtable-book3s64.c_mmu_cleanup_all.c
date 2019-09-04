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
struct TYPE_2__ {int /*<<< orphan*/  (* hpte_clear_all ) () ;} ;

/* Variables and functions */
 TYPE_1__ mmu_hash_ops ; 
 int /*<<< orphan*/  radix__mmu_cleanup_all () ; 
 scalar_t__ radix_enabled () ; 
 int /*<<< orphan*/  stub1 () ; 

void mmu_cleanup_all(void)
{
	if (radix_enabled())
		radix__mmu_cleanup_all();
	else if (mmu_hash_ops.hpte_clear_all)
		mmu_hash_ops.hpte_clear_all();
}