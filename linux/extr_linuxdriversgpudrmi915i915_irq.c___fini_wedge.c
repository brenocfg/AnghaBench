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
struct wedge_me {int /*<<< orphan*/ * i915; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_delayed_work_on_stack (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __fini_wedge(struct wedge_me *w)
{
	cancel_delayed_work_sync(&w->work);
	destroy_delayed_work_on_stack(&w->work);
	w->i915 = NULL;
}