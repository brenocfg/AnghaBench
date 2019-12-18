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
struct cache_set {int congested_last_us; int /*<<< orphan*/  congested; int /*<<< orphan*/  congested_write_threshold_us; int /*<<< orphan*/  congested_read_threshold_us; } ;

/* Variables and functions */
 scalar_t__ CONGESTED_MAX ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int fract_exp_two (int,int) ; 
 int /*<<< orphan*/  get_random_u32 () ; 
 scalar_t__ hweight32 (int /*<<< orphan*/ ) ; 
 int local_clock_us () ; 

unsigned int bch_get_congested(const struct cache_set *c)
{
	int i;

	if (!c->congested_read_threshold_us &&
	    !c->congested_write_threshold_us)
		return 0;

	i = (local_clock_us() - c->congested_last_us) / 1024;
	if (i < 0)
		return 0;

	i += atomic_read(&c->congested);
	if (i >= 0)
		return 0;

	i += CONGESTED_MAX;

	if (i > 0)
		i = fract_exp_two(i, 6);

	i -= hweight32(get_random_u32());

	return i > 0 ? i : 1;
}