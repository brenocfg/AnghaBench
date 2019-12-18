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
struct mmu_notifier_range {int /*<<< orphan*/  event; int /*<<< orphan*/  flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; struct mm_struct* mm; } ;
struct mmu_notifier {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_NOTIFY_UNMAP ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  radeon_mn_invalidate_range_start (struct mmu_notifier*,struct mmu_notifier_range*) ; 

__attribute__((used)) static void radeon_mn_release(struct mmu_notifier *mn, struct mm_struct *mm)
{
	struct mmu_notifier_range range = {
		.mm = mm,
		.start = 0,
		.end = ULONG_MAX,
		.flags = 0,
		.event = MMU_NOTIFY_UNMAP,
	};

	radeon_mn_invalidate_range_start(mn, &range);
}