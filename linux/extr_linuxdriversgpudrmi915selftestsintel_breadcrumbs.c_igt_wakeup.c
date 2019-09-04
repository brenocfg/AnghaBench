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
typedef  int u32 ;
struct intel_engine_cs {int dummy; } ;
struct igt_wakeup {int seqno; int /*<<< orphan*/  tsk; int /*<<< orphan*/  flags; struct intel_engine_cs* engine; int /*<<< orphan*/ * done; int /*<<< orphan*/ * set; int /*<<< orphan*/ * ready; int /*<<< orphan*/ * wq; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECLARE_WAIT_QUEUE_HEAD_ONSTACK (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  I915_RND_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDLE ; 
 int INT_MAX ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STOP ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int const) ; 
 int check_rbtree_empty (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  get_task_struct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igt_wake_all_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  igt_wakeup_thread ; 
 int intel_engine_get_seqno (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct igt_wakeup*,char*,int) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (struct igt_wakeup*) ; 
 struct igt_wakeup* kvmalloc_array (int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mock_engine_flush (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  mock_engine_reset (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  mock_seqno_advance (struct intel_engine_cs*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int const prandom_u32_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prng ; 
 int /*<<< orphan*/  put_task_struct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wait_var_event_timeout (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wq ; 

__attribute__((used)) static int igt_wakeup(void *arg)
{
	I915_RND_STATE(prng);
	struct intel_engine_cs *engine = arg;
	struct igt_wakeup *waiters;
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);
	const int count = 4096;
	const u32 max_seqno = count / 4;
	atomic_t ready, set, done;
	int err = -ENOMEM;
	int n, step;

	mock_engine_reset(engine);

	waiters = kvmalloc_array(count, sizeof(*waiters), GFP_KERNEL);
	if (!waiters)
		goto out_engines;

	/* Create a large number of threads, each waiting on a random seqno.
	 * Multiple waiters will be waiting for the same seqno.
	 */
	atomic_set(&ready, count);
	for (n = 0; n < count; n++) {
		waiters[n].wq = &wq;
		waiters[n].ready = &ready;
		waiters[n].set = &set;
		waiters[n].done = &done;
		waiters[n].engine = engine;
		waiters[n].flags = BIT(IDLE);

		waiters[n].tsk = kthread_run(igt_wakeup_thread, &waiters[n],
					     "i915/igt:%d", n);
		if (IS_ERR(waiters[n].tsk))
			goto out_waiters;

		get_task_struct(waiters[n].tsk);
	}

	for (step = 1; step <= max_seqno; step <<= 1) {
		u32 seqno;

		/* The waiter threads start paused as we assign them a random
		 * seqno and reset the engine. Once the engine is reset,
		 * we signal that the threads may begin their wait upon their
		 * seqno.
		 */
		for (n = 0; n < count; n++) {
			GEM_BUG_ON(!test_bit(IDLE, &waiters[n].flags));
			waiters[n].seqno =
				1 + prandom_u32_state(&prng) % max_seqno;
		}
		mock_seqno_advance(engine, 0);
		igt_wake_all_sync(&ready, &set, &done, &wq, count);

		/* Simulate the GPU doing chunks of work, with one or more
		 * seqno appearing to finish at the same time. A random number
		 * of threads will be waiting upon the update and hopefully be
		 * woken.
		 */
		for (seqno = 1; seqno <= max_seqno + step; seqno += step) {
			usleep_range(50, 500);
			mock_seqno_advance(engine, seqno);
		}
		GEM_BUG_ON(intel_engine_get_seqno(engine) < 1 + max_seqno);

		/* With the seqno now beyond any of the waiting threads, they
		 * should all be woken, see that they are complete and signal
		 * that they are ready for the next test. We wait until all
		 * threads are complete and waiting for us (i.e. not a seqno).
		 */
		if (!wait_var_event_timeout(&done,
					    !atomic_read(&done), 10 * HZ)) {
			pr_err("Timed out waiting for %d remaining waiters\n",
			       atomic_read(&done));
			err = -ETIMEDOUT;
			break;
		}

		err = check_rbtree_empty(engine);
		if (err)
			break;
	}

out_waiters:
	for (n = 0; n < count; n++) {
		if (IS_ERR(waiters[n].tsk))
			break;

		set_bit(STOP, &waiters[n].flags);
	}
	mock_seqno_advance(engine, INT_MAX); /* wakeup any broken waiters */
	igt_wake_all_sync(&ready, &set, &done, &wq, n);

	for (n = 0; n < count; n++) {
		if (IS_ERR(waiters[n].tsk))
			break;

		kthread_stop(waiters[n].tsk);
		put_task_struct(waiters[n].tsk);
	}

	kvfree(waiters);
out_engines:
	mock_engine_flush(engine);
	return err;
}