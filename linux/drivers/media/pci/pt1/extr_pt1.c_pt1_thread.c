#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pt1_buffer_page {int dummy; } ;
struct pt1 {size_t table_index; size_t buf_index; TYPE_3__* tables; TYPE_1__** adaps; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_6__ {TYPE_2__* bufs; } ;
struct TYPE_5__ {struct pt1_buffer_page* page; } ;
struct TYPE_4__ {int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int NSEC_PER_MSEC ; 
 int PT1_FETCH_DELAY ; 
 int PT1_FETCH_DELAY_DELTA ; 
 int PT1_NR_ADAPS ; 
 size_t PT1_NR_BUFS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  kthread_freezable_should_stop (int*) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pt1_filter (struct pt1*,struct pt1_buffer_page*) ; 
 int /*<<< orphan*/  pt1_increment_table_count (struct pt1*) ; 
 scalar_t__ pt1_nr_tables ; 
 int /*<<< orphan*/  pt1_set_stream (struct pt1*,int,int) ; 
 int /*<<< orphan*/  schedule_hrtimeout_range (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 

__attribute__((used)) static int pt1_thread(void *data)
{
	struct pt1 *pt1;
	struct pt1_buffer_page *page;
	bool was_frozen;

#define PT1_FETCH_DELAY 10
#define PT1_FETCH_DELAY_DELTA 2

	pt1 = data;
	set_freezable();

	while (!kthread_freezable_should_stop(&was_frozen)) {
		if (was_frozen) {
			int i;

			for (i = 0; i < PT1_NR_ADAPS; i++)
				pt1_set_stream(pt1, i, !!pt1->adaps[i]->users);
		}

		page = pt1->tables[pt1->table_index].bufs[pt1->buf_index].page;
		if (!pt1_filter(pt1, page)) {
			ktime_t delay;

			delay = ktime_set(0, PT1_FETCH_DELAY * NSEC_PER_MSEC);
			set_current_state(TASK_INTERRUPTIBLE);
			schedule_hrtimeout_range(&delay,
					PT1_FETCH_DELAY_DELTA * NSEC_PER_MSEC,
					HRTIMER_MODE_REL);
			continue;
		}

		if (++pt1->buf_index >= PT1_NR_BUFS) {
			pt1_increment_table_count(pt1);
			pt1->buf_index = 0;
			if (++pt1->table_index >= pt1_nr_tables)
				pt1->table_index = 0;
		}
	}

	return 0;
}