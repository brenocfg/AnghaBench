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
struct intel_wakeref {int /*<<< orphan*/  rpm; int /*<<< orphan*/  wakeref; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_WAKEREF_BUG_ON (int) ; 
 int /*<<< orphan*/  fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rpm_put(struct intel_wakeref *wf)
{
	intel_wakeref_t wakeref = fetch_and_zero(&wf->wakeref);

	intel_runtime_pm_put(wf->rpm, wakeref);
	INTEL_WAKEREF_BUG_ON(!wakeref);
}