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
struct etnaviv_gpu {int /*<<< orphan*/  event_free; int /*<<< orphan*/  event_spinlock; int /*<<< orphan*/  event_bitmap; int /*<<< orphan*/ * event; int /*<<< orphan*/  dev; } ;
struct etnaviv_event {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ETNA_NR_EVENTS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int event_alloc(struct etnaviv_gpu *gpu, unsigned nr_events,
	unsigned int *events)
{
	unsigned long timeout = msecs_to_jiffies(10 * 10000);
	unsigned i, acquired = 0;

	for (i = 0; i < nr_events; i++) {
		unsigned long ret;

		ret = wait_for_completion_timeout(&gpu->event_free, timeout);

		if (!ret) {
			dev_err(gpu->dev, "wait_for_completion_timeout failed");
			goto out;
		}

		acquired++;
		timeout = ret;
	}

	spin_lock(&gpu->event_spinlock);

	for (i = 0; i < nr_events; i++) {
		int event = find_first_zero_bit(gpu->event_bitmap, ETNA_NR_EVENTS);

		events[i] = event;
		memset(&gpu->event[event], 0, sizeof(struct etnaviv_event));
		set_bit(event, gpu->event_bitmap);
	}

	spin_unlock(&gpu->event_spinlock);

	return 0;

out:
	for (i = 0; i < acquired; i++)
		complete(&gpu->event_free);

	return -EBUSY;
}