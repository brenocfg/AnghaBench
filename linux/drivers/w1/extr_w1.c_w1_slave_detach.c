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
struct w1_slave {TYPE_1__* master; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  list_mutex; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  W1_SLAVE_DETACH ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w1_unref_slave (struct w1_slave*) ; 

int w1_slave_detach(struct w1_slave *sl)
{
	/* Only detach a slave once as it decreases the refcnt each time. */
	int destroy_now;
	mutex_lock(&sl->master->list_mutex);
	destroy_now = !test_bit(W1_SLAVE_DETACH, &sl->flags);
	set_bit(W1_SLAVE_DETACH, &sl->flags);
	mutex_unlock(&sl->master->list_mutex);

	if (destroy_now)
		destroy_now = !w1_unref_slave(sl);
	return destroy_now ? 0 : -EBUSY;
}