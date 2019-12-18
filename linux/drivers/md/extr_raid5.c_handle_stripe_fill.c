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
struct stripe_head_state {scalar_t__ failed; scalar_t__ injournal; } ;
struct stripe_head {int /*<<< orphan*/  state; int /*<<< orphan*/  reconstruct_state; int /*<<< orphan*/  check_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRIPE_COMPUTE_RUN ; 
 int /*<<< orphan*/  STRIPE_HANDLE ; 
 int /*<<< orphan*/  STRIPE_R5C_CACHING ; 
 scalar_t__ fetch_block (struct stripe_head*,struct stripe_head_state*,int,int) ; 
 int /*<<< orphan*/  r5c_make_stripe_write_out (struct stripe_head*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_stripe_fill(struct stripe_head *sh,
			       struct stripe_head_state *s,
			       int disks)
{
	int i;

	/* look for blocks to read/compute, skip this if a compute
	 * is already in flight, or if the stripe contents are in the
	 * midst of changing due to a write
	 */
	if (!test_bit(STRIPE_COMPUTE_RUN, &sh->state) && !sh->check_state &&
	    !sh->reconstruct_state) {

		/*
		 * For degraded stripe with data in journal, do not handle
		 * read requests yet, instead, flush the stripe to raid
		 * disks first, this avoids handling complex rmw of write
		 * back cache (prexor with orig_page, and then xor with
		 * page) in the read path
		 */
		if (s->injournal && s->failed) {
			if (test_bit(STRIPE_R5C_CACHING, &sh->state))
				r5c_make_stripe_write_out(sh);
			goto out;
		}

		for (i = disks; i--; )
			if (fetch_block(sh, s, i, disks))
				break;
	}
out:
	set_bit(STRIPE_HANDLE, &sh->state);
}