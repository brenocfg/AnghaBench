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
struct intel_uncore_forcewake_domain {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORCEWAKE_KERNEL ; 
 int /*<<< orphan*/  TAINT_WARN ; 
 int /*<<< orphan*/  add_taint_for_CI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_domain_to_str (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_ack_set (struct intel_uncore_forcewake_domain const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
fw_domain_wait_ack_set(const struct intel_uncore_forcewake_domain *d)
{
	if (wait_ack_set(d, FORCEWAKE_KERNEL)) {
		DRM_ERROR("%s: timed out waiting for forcewake ack request.\n",
			  intel_uncore_forcewake_domain_to_str(d->id));
		add_taint_for_CI(TAINT_WARN); /* CI now unreliable */
	}
}