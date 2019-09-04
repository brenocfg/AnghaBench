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
struct ad7879 {int disabled; TYPE_1__* input; int /*<<< orphan*/  suspended; } ;
struct TYPE_2__ {scalar_t__ users; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ad7879_disable (struct ad7879*) ; 
 int /*<<< orphan*/  __ad7879_enable (struct ad7879*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ad7879_toggle(struct ad7879 *ts, bool disable)
{
	mutex_lock(&ts->input->mutex);

	if (!ts->suspended && ts->input->users != 0) {

		if (disable) {
			if (ts->disabled)
				__ad7879_enable(ts);
		} else {
			if (!ts->disabled)
				__ad7879_disable(ts);
		}
	}

	ts->disabled = disable;

	mutex_unlock(&ts->input->mutex);
}