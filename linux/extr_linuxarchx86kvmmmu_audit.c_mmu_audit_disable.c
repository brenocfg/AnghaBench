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
 int mmu_audit ; 
 int /*<<< orphan*/  mmu_audit_key ; 
 int /*<<< orphan*/  static_key_slow_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmu_audit_disable(void)
{
	if (!mmu_audit)
		return;

	static_key_slow_dec(&mmu_audit_key);
	mmu_audit = false;
}