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

/* Variables and functions */
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rpm_get(struct intel_wakeref *wf)
{
	wf->wakeref = intel_runtime_pm_get(wf->rpm);
}