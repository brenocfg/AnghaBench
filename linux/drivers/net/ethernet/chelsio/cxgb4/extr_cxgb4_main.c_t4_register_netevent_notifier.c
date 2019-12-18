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

/* Variables and functions */
 int /*<<< orphan*/  cxgb4_netevent_nb ; 
 int netevent_registered ; 
 int /*<<< orphan*/  register_netevent_notifier (int /*<<< orphan*/ *) ; 

void t4_register_netevent_notifier(void)
{
	if (!netevent_registered) {
		register_netevent_notifier(&cxgb4_netevent_nb);
		netevent_registered = true;
	}
}