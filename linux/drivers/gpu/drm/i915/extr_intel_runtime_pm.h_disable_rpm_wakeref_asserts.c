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
struct intel_runtime_pm {int /*<<< orphan*/  wakeref_count; } ;

/* Variables and functions */
 scalar_t__ INTEL_RPM_WAKELOCK_BIAS ; 
 int /*<<< orphan*/  atomic_add (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
disable_rpm_wakeref_asserts(struct intel_runtime_pm *rpm)
{
	atomic_add(INTEL_RPM_WAKELOCK_BIAS + 1,
		   &rpm->wakeref_count);
}