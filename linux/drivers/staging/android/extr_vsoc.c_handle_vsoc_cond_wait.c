#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u32 ;
struct vsoc_region_data {int /*<<< orphan*/  futex_wait_queue; } ;
struct vsoc_device_region {scalar_t__ region_begin_offset; scalar_t__ region_end_offset; } ;
struct vsoc_cond_wait {int offset; int wait_type; scalar_t__ wake_time_nsec; scalar_t__ value; int /*<<< orphan*/  wakes; int /*<<< orphan*/  wake_time_sec; } ;
struct hrtimer_sleeper {int /*<<< orphan*/  timer; int /*<<< orphan*/  task; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_5__ {int /*<<< orphan*/  timer_slack_ns; } ;
struct TYPE_4__ {struct vsoc_region_data* regions_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int E2BIG ; 
 int EADDRNOTAVAIL ; 
 int EINTR ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 scalar_t__ NSEC_PER_SEC ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
#define  VSOC_WAIT_IF_EQUAL 129 
#define  VSOC_WAIT_IF_EQUAL_TIMEOUT 128 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  destroy_hrtimer_on_stack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freezable_schedule () ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_init_sleeper_on_stack (struct hrtimer_sleeper*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_set_expires_range_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_sleeper_start_expires (struct hrtimer_sleeper*,int /*<<< orphan*/ ) ; 
 int iminor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * shm_off_to_virtual_addr (scalar_t__) ; 
 scalar_t__ signal_pending (TYPE_2__*) ; 
 TYPE_1__ vsoc_dev ; 
 struct vsoc_device_region* vsoc_region_from_filep (struct file*) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int handle_vsoc_cond_wait(struct file *filp, struct vsoc_cond_wait *arg)
{
	DEFINE_WAIT(wait);
	u32 region_number = iminor(file_inode(filp));
	struct vsoc_region_data *data = vsoc_dev.regions_data + region_number;
	struct hrtimer_sleeper timeout, *to = NULL;
	int ret = 0;
	struct vsoc_device_region *region_p = vsoc_region_from_filep(filp);
	atomic_t *address = NULL;
	ktime_t wake_time;

	/* Ensure that the offset is aligned */
	if (arg->offset & (sizeof(uint32_t) - 1))
		return -EADDRNOTAVAIL;
	/* Ensure that the offset is within shared memory */
	if (((uint64_t)arg->offset) + region_p->region_begin_offset +
	    sizeof(uint32_t) > region_p->region_end_offset)
		return -E2BIG;
	address = shm_off_to_virtual_addr(region_p->region_begin_offset +
					  arg->offset);

	/* Ensure that the type of wait is valid */
	switch (arg->wait_type) {
	case VSOC_WAIT_IF_EQUAL:
		break;
	case VSOC_WAIT_IF_EQUAL_TIMEOUT:
		to = &timeout;
		break;
	default:
		return -EINVAL;
	}

	if (to) {
		/* Copy the user-supplied timesec into the kernel structure.
		 * We do things this way to flatten differences between 32 bit
		 * and 64 bit timespecs.
		 */
		if (arg->wake_time_nsec >= NSEC_PER_SEC)
			return -EINVAL;
		wake_time = ktime_set(arg->wake_time_sec, arg->wake_time_nsec);

		hrtimer_init_sleeper_on_stack(to, CLOCK_MONOTONIC,
					      HRTIMER_MODE_ABS);
		hrtimer_set_expires_range_ns(&to->timer, wake_time,
					     current->timer_slack_ns);
	}

	while (1) {
		prepare_to_wait(&data->futex_wait_queue, &wait,
				TASK_INTERRUPTIBLE);
		/*
		 * Check the sentinel value after prepare_to_wait. If the value
		 * changes after this check the writer will call signal,
		 * changing the task state from INTERRUPTIBLE to RUNNING. That
		 * will ensure that schedule() will eventually schedule this
		 * task.
		 */
		if (atomic_read(address) != arg->value) {
			ret = 0;
			break;
		}
		if (to) {
			hrtimer_sleeper_start_expires(to, HRTIMER_MODE_ABS);
			if (likely(to->task))
				freezable_schedule();
			hrtimer_cancel(&to->timer);
			if (!to->task) {
				ret = -ETIMEDOUT;
				break;
			}
		} else {
			freezable_schedule();
		}
		/* Count the number of times that we woke up. This is useful
		 * for unit testing.
		 */
		++arg->wakes;
		if (signal_pending(current)) {
			ret = -EINTR;
			break;
		}
	}
	finish_wait(&data->futex_wait_queue, &wait);
	if (to)
		destroy_hrtimer_on_stack(&to->timer);
	return ret;
}