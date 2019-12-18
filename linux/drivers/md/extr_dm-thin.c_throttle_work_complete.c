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
struct throttle {int throttle_applied; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void throttle_work_complete(struct throttle *t)
{
	if (t->throttle_applied) {
		t->throttle_applied = false;
		up_write(&t->lock);
	}
}