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
struct perf_thread {int /*<<< orphan*/  work; int /*<<< orphan*/  duration; scalar_t__ copied; int /*<<< orphan*/  status; } ;
struct perf_peer {int /*<<< orphan*/  sts; struct perf_ctx* perf; } ;
struct perf_ctx {int tcnt; int /*<<< orphan*/  busy_flag; int /*<<< orphan*/  tsync; int /*<<< orphan*/  twait; struct perf_thread* threads; struct perf_peer* test_peer; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINTR ; 
 int /*<<< orphan*/  ENODATA ; 
 int ENOLINK ; 
 int ERESTARTSYS ; 
 int MAX_THREADS_CNT ; 
 int /*<<< orphan*/  PERF_STS_DONE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_terminate_test (struct perf_ctx*) ; 
 int /*<<< orphan*/  perf_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int perf_submit_test(struct perf_peer *peer)
{
	struct perf_ctx *perf = peer->perf;
	struct perf_thread *pthr;
	int tidx, ret;

	if (!test_bit(PERF_STS_DONE, &peer->sts))
		return -ENOLINK;

	if (test_and_set_bit_lock(0, &perf->busy_flag))
		return -EBUSY;

	perf->test_peer = peer;
	atomic_set(&perf->tsync, perf->tcnt);

	for (tidx = 0; tidx < MAX_THREADS_CNT; tidx++) {
		pthr = &perf->threads[tidx];

		pthr->status = -ENODATA;
		pthr->copied = 0;
		pthr->duration = ktime_set(0, 0);
		if (tidx < perf->tcnt)
			(void)queue_work(perf_wq, &pthr->work);
	}

	ret = wait_event_interruptible(perf->twait,
				       atomic_read(&perf->tsync) <= 0);
	if (ret == -ERESTARTSYS) {
		perf_terminate_test(perf);
		ret = -EINTR;
	}

	clear_bit_unlock(0, &perf->busy_flag);

	return ret;
}