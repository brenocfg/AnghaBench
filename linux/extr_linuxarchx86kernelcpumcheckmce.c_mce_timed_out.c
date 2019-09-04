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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ s64 ;
struct TYPE_2__ {int tolerant; int /*<<< orphan*/  monarch_timeout; } ;

/* Variables and functions */
 scalar_t__ SPINUNIT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int cpu_missing ; 
 TYPE_1__ mca_cfg ; 
 int /*<<< orphan*/  mce_panic (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mce_panicked ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  touch_nmi_watchdog () ; 
 int /*<<< orphan*/  wait_for_panic () ; 

__attribute__((used)) static int mce_timed_out(u64 *t, const char *msg)
{
	/*
	 * The others already did panic for some reason.
	 * Bail out like in a timeout.
	 * rmb() to tell the compiler that system_state
	 * might have been modified by someone else.
	 */
	rmb();
	if (atomic_read(&mce_panicked))
		wait_for_panic();
	if (!mca_cfg.monarch_timeout)
		goto out;
	if ((s64)*t < SPINUNIT) {
		if (mca_cfg.tolerant <= 1)
			mce_panic(msg, NULL, NULL);
		cpu_missing = 1;
		return 1;
	}
	*t -= SPINUNIT;
out:
	touch_nmi_watchdog();
	return 0;
}