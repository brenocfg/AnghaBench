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
struct intel_wait {int /*<<< orphan*/  node; int /*<<< orphan*/  seqno; } ;
struct intel_engine_cs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_LONG ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int const,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  __set_bit (int,unsigned long*) ; 
 int check_completion (struct intel_engine_cs*,unsigned long*,struct intel_wait*,int const) ; 
 int check_rbtree (struct intel_engine_cs*,unsigned long*,struct intel_wait*,int const) ; 
 int check_rbtree_empty (struct intel_engine_cs*) ; 
 int find_first_bit (unsigned long*,int const) ; 
 int /*<<< orphan*/  intel_engine_add_wait (struct intel_engine_cs*,struct intel_wait*) ; 
 int /*<<< orphan*/  intel_engine_remove_wait (struct intel_engine_cs*,struct intel_wait*) ; 
 scalar_t__ intel_wait_complete (struct intel_wait*) ; 
 int /*<<< orphan*/  intel_wait_init_for_seqno (struct intel_wait*,int const) ; 
 unsigned long* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 int /*<<< orphan*/  kvfree (struct intel_wait*) ; 
 struct intel_wait* kvmalloc_array (int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mock_engine_flush (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  mock_engine_reset (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  mock_seqno_advance (struct intel_engine_cs*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 int /*<<< orphan*/  test_bit (int,unsigned long*) ; 

__attribute__((used)) static int igt_insert_complete(void *arg)
{
	const u32 seqno_bias = 0x1000;
	struct intel_engine_cs *engine = arg;
	struct intel_wait *waiters;
	const int count = 4096;
	unsigned long *bitmap;
	int err = -ENOMEM;
	int n, m;

	mock_engine_reset(engine);

	waiters = kvmalloc_array(count, sizeof(*waiters), GFP_KERNEL);
	if (!waiters)
		goto out_engines;

	bitmap = kcalloc(DIV_ROUND_UP(count, BITS_PER_LONG), sizeof(*bitmap),
			 GFP_KERNEL);
	if (!bitmap)
		goto out_waiters;

	for (n = 0; n < count; n++) {
		intel_wait_init_for_seqno(&waiters[n], n + seqno_bias);
		intel_engine_add_wait(engine, &waiters[n]);
		__set_bit(n, bitmap);
	}
	err = check_rbtree(engine, bitmap, waiters, count);
	if (err)
		goto out_bitmap;

	/* On each step, we advance the seqno so that several waiters are then
	 * complete (we increase the seqno by increasingly larger values to
	 * retire more and more waiters at once). All retired waiters should
	 * be woken and removed from the rbtree, and so that we check.
	 */
	for (n = 0; n < count; n = m) {
		int seqno = 2 * n;

		GEM_BUG_ON(find_first_bit(bitmap, count) != n);

		if (intel_wait_complete(&waiters[n])) {
			pr_err("waiter[%d, seqno=%d] completed too early\n",
			       n, waiters[n].seqno);
			err = -EINVAL;
			goto out_bitmap;
		}

		/* complete the following waiters */
		mock_seqno_advance(engine, seqno + seqno_bias);
		for (m = n; m <= seqno; m++) {
			if (m == count)
				break;

			GEM_BUG_ON(!test_bit(m, bitmap));
			__clear_bit(m, bitmap);
		}

		intel_engine_remove_wait(engine, &waiters[n]);
		RB_CLEAR_NODE(&waiters[n].node);

		err = check_rbtree(engine, bitmap, waiters, count);
		if (err) {
			pr_err("rbtree corrupt after seqno advance to %d\n",
			       seqno + seqno_bias);
			goto out_bitmap;
		}

		err = check_completion(engine, bitmap, waiters, count);
		if (err) {
			pr_err("completions after seqno advance to %d failed\n",
			       seqno + seqno_bias);
			goto out_bitmap;
		}
	}

	err = check_rbtree_empty(engine);
out_bitmap:
	kfree(bitmap);
out_waiters:
	kvfree(waiters);
out_engines:
	mock_engine_flush(engine);
	return err;
}