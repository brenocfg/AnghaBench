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
struct intel_uncore_forcewake_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_SET ; 
 int /*<<< orphan*/  FORCEWAKE_KERNEL ; 
 int /*<<< orphan*/  fw_domain_wait_ack_set (struct intel_uncore_forcewake_domain const*) ; 
 scalar_t__ fw_domain_wait_ack_with_fallback (struct intel_uncore_forcewake_domain const*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  wait_ack_set (struct intel_uncore_forcewake_domain const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
fw_domain_wait_ack_set_fallback(const struct intel_uncore_forcewake_domain *d)
{
	if (likely(!wait_ack_set(d, FORCEWAKE_KERNEL)))
		return;

	if (fw_domain_wait_ack_with_fallback(d, ACK_SET))
		fw_domain_wait_ack_set(d);
}