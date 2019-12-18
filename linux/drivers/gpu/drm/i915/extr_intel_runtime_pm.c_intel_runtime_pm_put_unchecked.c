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
struct intel_runtime_pm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __intel_runtime_pm_put (struct intel_runtime_pm*,int,int) ; 

void intel_runtime_pm_put_unchecked(struct intel_runtime_pm *rpm)
{
	__intel_runtime_pm_put(rpm, -1, true);
}