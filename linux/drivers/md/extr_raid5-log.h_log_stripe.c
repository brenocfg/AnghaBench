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
struct stripe_head_state {scalar_t__ waiting_extra_page; } ;
struct stripe_head {int /*<<< orphan*/  state; struct r5conf* raid_conf; } ;
struct r5conf {scalar_t__ log; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  STRIPE_LOG_TRAPPED ; 
 int /*<<< orphan*/  STRIPE_R5C_CACHING ; 
 int ppl_write_stripe (struct r5conf*,struct stripe_head*) ; 
 int r5c_cache_data (scalar_t__,struct stripe_head*) ; 
 int r5l_write_stripe (scalar_t__,struct stripe_head*) ; 
 scalar_t__ raid5_has_ppl (struct r5conf*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int log_stripe(struct stripe_head *sh, struct stripe_head_state *s)
{
	struct r5conf *conf = sh->raid_conf;

	if (conf->log) {
		if (!test_bit(STRIPE_R5C_CACHING, &sh->state)) {
			/* writing out phase */
			if (s->waiting_extra_page)
				return 0;
			return r5l_write_stripe(conf->log, sh);
		} else if (test_bit(STRIPE_LOG_TRAPPED, &sh->state)) {
			/* caching phase */
			return r5c_cache_data(conf->log, sh);
		}
	} else if (raid5_has_ppl(conf)) {
		return ppl_write_stripe(conf, sh);
	}

	return -EAGAIN;
}