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
struct TYPE_2__ {int /*<<< orphan*/  force_wake_get; } ;
struct intel_uncore {int /*<<< orphan*/  fw_domains_active; TYPE_1__ funcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void assert_forcewakes_inactive(struct intel_uncore *uncore)
{
	if (!uncore->funcs.force_wake_get)
		return;

	WARN(uncore->fw_domains_active,
	     "Expected all fw_domains to be inactive, but %08x are still on\n",
	     uncore->fw_domains_active);
}