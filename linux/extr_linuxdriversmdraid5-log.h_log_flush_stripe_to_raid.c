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
struct r5conf {scalar_t__ log; } ;

/* Variables and functions */
 int /*<<< orphan*/  ppl_write_stripe_run (struct r5conf*) ; 
 int /*<<< orphan*/  r5l_flush_stripe_to_raid (scalar_t__) ; 
 scalar_t__ raid5_has_ppl (struct r5conf*) ; 

__attribute__((used)) static inline void log_flush_stripe_to_raid(struct r5conf *conf)
{
	if (conf->log)
		r5l_flush_stripe_to_raid(conf->log);
	else if (raid5_has_ppl(conf))
		ppl_write_stripe_run(conf);
}