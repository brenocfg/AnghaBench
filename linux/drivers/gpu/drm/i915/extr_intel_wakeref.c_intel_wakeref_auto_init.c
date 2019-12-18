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
struct intel_wakeref_auto {struct intel_runtime_pm* rpm; scalar_t__ wakeref; int /*<<< orphan*/  count; int /*<<< orphan*/  timer; int /*<<< orphan*/  lock; } ;
struct intel_runtime_pm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeref_auto_timeout ; 

void intel_wakeref_auto_init(struct intel_wakeref_auto *wf,
			     struct intel_runtime_pm *rpm)
{
	spin_lock_init(&wf->lock);
	timer_setup(&wf->timer, wakeref_auto_timeout, 0);
	refcount_set(&wf->count, 0);
	wf->wakeref = 0;
	wf->rpm = rpm;
}