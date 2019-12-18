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
struct mapped_device {int /*<<< orphan*/  flags; scalar_t__ internal_suspend_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMF_SUSPENDED_INTERNALLY ; 
 int /*<<< orphan*/  __dm_resume (struct mapped_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dm_suspended_md (struct mapped_device*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __dm_internal_resume(struct mapped_device *md)
{
	BUG_ON(!md->internal_suspend_count);

	if (--md->internal_suspend_count)
		return; /* resume from nested internal suspend */

	if (dm_suspended_md(md))
		goto done; /* resume from nested suspend */

	/*
	 * NOTE: existing callers don't need to call dm_table_resume_targets
	 * (which may fail -- so best to avoid it for now by passing NULL map)
	 */
	(void) __dm_resume(md, NULL);

done:
	clear_bit(DMF_SUSPENDED_INTERNALLY, &md->flags);
	smp_mb__after_atomic();
	wake_up_bit(&md->flags, DMF_SUSPENDED_INTERNALLY);
}