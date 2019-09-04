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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct i915_syncmap {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int HZ ; 
 int /*<<< orphan*/  I915_RND_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IGT_TIMEOUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __igt_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctx ; 
 int dump_syncmap (struct i915_syncmap*,int) ; 
 int /*<<< orphan*/  end_time ; 
 int /*<<< orphan*/  i915_prandom_u64_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_syncmap_init (struct i915_syncmap**) ; 
 int i915_syncmap_is_later (struct i915_syncmap**,int /*<<< orphan*/ ,scalar_t__) ; 
 int i915_syncmap_set (struct i915_syncmap**,int /*<<< orphan*/ ,scalar_t__) ; 
 int jiffies ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 scalar_t__ prandom_u32_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prng ; 
 int seqno_later (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  time_after (int,unsigned long) ; 

__attribute__((used)) static int igt_syncmap_random(void *arg)
{
	I915_RND_STATE(prng);
	IGT_TIMEOUT(end_time);
	struct i915_syncmap *sync;
	unsigned long count, phase, i;
	u32 seqno;
	int err;

	i915_syncmap_init(&sync);

	/*
	 * Having tried to test the individual operations within i915_syncmap,
	 * run a smoketest exploring the entire u64 space with random
	 * insertions.
	 */

	count = 0;
	phase = jiffies + HZ/100 + 1;
	do {
		u64 context = i915_prandom_u64_state(&prng);

		err = i915_syncmap_set(&sync, context, 0);
		if (err)
			goto out;

		count++;
	} while (!time_after(jiffies, phase));
	seqno = 0;

	phase = 0;
	do {
		I915_RND_STATE(ctx);
		u32 last_seqno = seqno;
		bool expect;

		seqno = prandom_u32_state(&prng);
		expect = seqno_later(last_seqno, seqno);

		for (i = 0; i < count; i++) {
			u64 context = i915_prandom_u64_state(&ctx);

			if (i915_syncmap_is_later(&sync, context, seqno) != expect) {
				pr_err("context=%llu, last=%u this=%u did not match expectation (%d)\n",
				       context, last_seqno, seqno, expect);
				err = -EINVAL;
				goto out;
			}

			err = i915_syncmap_set(&sync, context, seqno);
			if (err)
				goto out;
		}

		phase++;
	} while (!__igt_timeout(end_time, NULL));
	pr_debug("Completed %lu passes, each of %lu contexts\n", phase, count);
out:
	return dump_syncmap(sync, err);
}