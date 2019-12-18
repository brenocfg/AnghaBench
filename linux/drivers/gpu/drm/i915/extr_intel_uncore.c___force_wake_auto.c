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
struct intel_uncore {int fw_domains; int fw_domains_active; } ;
typedef  enum forcewake_domains { ____Placeholder_forcewake_domains } forcewake_domains ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  ___force_wake_auto (struct intel_uncore*,int) ; 

__attribute__((used)) static inline void __force_wake_auto(struct intel_uncore *uncore,
				     enum forcewake_domains fw_domains)
{
	GEM_BUG_ON(!fw_domains);

	/* Turn on all requested but inactive supported forcewake domains. */
	fw_domains &= uncore->fw_domains;
	fw_domains &= ~uncore->fw_domains_active;

	if (fw_domains)
		___force_wake_auto(uncore, fw_domains);
}