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
struct intel_wakeref_auto {int /*<<< orphan*/  wakeref; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_WAKEREF_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_wakeref_auto (struct intel_wakeref_auto*,int /*<<< orphan*/ ) ; 

void intel_wakeref_auto_fini(struct intel_wakeref_auto *wf)
{
	intel_wakeref_auto(wf, 0);
	INTEL_WAKEREF_BUG_ON(wf->wakeref);
}