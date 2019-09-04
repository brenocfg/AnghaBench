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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long build_cr3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long build_cr3_noflush (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_user_asid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cr3 (unsigned long) ; 

__attribute__((used)) static void load_new_mm_cr3(pgd_t *pgdir, u16 new_asid, bool need_flush)
{
	unsigned long new_mm_cr3;

	if (need_flush) {
		invalidate_user_asid(new_asid);
		new_mm_cr3 = build_cr3(pgdir, new_asid);
	} else {
		new_mm_cr3 = build_cr3_noflush(pgdir, new_asid);
	}

	/*
	 * Caution: many callers of this function expect
	 * that load_cr3() is serializing and orders TLB
	 * fills with respect to the mm_cpumask writes.
	 */
	write_cr3(new_mm_cr3);
}