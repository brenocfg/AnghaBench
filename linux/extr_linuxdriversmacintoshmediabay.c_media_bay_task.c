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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  sleeping; } ;

/* Variables and functions */
 int /*<<< orphan*/  MB_POLL_DELAY ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int media_bay_count ; 
 int /*<<< orphan*/  media_bay_step (int) ; 
 TYPE_1__* media_bays ; 
 int /*<<< orphan*/  msleep_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int media_bay_task(void *x)
{
	int	i;

	while (!kthread_should_stop()) {
		for (i = 0; i < media_bay_count; ++i) {
			mutex_lock(&media_bays[i].lock);
			if (!media_bays[i].sleeping)
				media_bay_step(i);
			mutex_unlock(&media_bays[i].lock);
		}

		msleep_interruptible(MB_POLL_DELAY);
	}
	return 0;
}