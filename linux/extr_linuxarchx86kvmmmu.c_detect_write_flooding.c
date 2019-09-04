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
struct TYPE_2__ {scalar_t__ level; } ;
struct kvm_mmu_page {int /*<<< orphan*/  write_flooding_count; TYPE_1__ role; } ;

/* Variables and functions */
 scalar_t__ PT_PAGE_TABLE_LEVEL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool detect_write_flooding(struct kvm_mmu_page *sp)
{
	/*
	 * Skip write-flooding detected for the sp whose level is 1, because
	 * it can become unsync, then the guest page is not write-protected.
	 */
	if (sp->role.level == PT_PAGE_TABLE_LEVEL)
		return false;

	atomic_inc(&sp->write_flooding_count);
	return atomic_read(&sp->write_flooding_count) >= 3;
}