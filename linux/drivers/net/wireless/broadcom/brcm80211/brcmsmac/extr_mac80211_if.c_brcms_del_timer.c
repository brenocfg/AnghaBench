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
struct brcms_timer {int set; TYPE_1__* wl; int /*<<< orphan*/  dly_wrk; } ;
struct TYPE_2__ {int /*<<< orphan*/  callbacks; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 

bool brcms_del_timer(struct brcms_timer *t)
{
	if (t->set) {
		t->set = false;
		if (!cancel_delayed_work(&t->dly_wrk))
			return false;

		atomic_dec(&t->wl->callbacks);
	}

	return true;
}