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
struct r5conf {int chunk_sectors; int /*<<< orphan*/  log; int /*<<< orphan*/  r5c_cached_full_stripes; } ;

/* Variables and functions */
 int /*<<< orphan*/  R5C_FULL_STRIPE_FLUSH_BATCH (struct r5conf*) ; 
 int STRIPE_SHIFT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r5c_is_writeback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r5l_wake_reclaim (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void r5c_check_cached_full_stripe(struct r5conf *conf)
{
	if (!r5c_is_writeback(conf->log))
		return;

	/*
	 * wake up reclaim for R5C_FULL_STRIPE_FLUSH_BATCH cached stripes
	 * or a full stripe (chunk size / 4k stripes).
	 */
	if (atomic_read(&conf->r5c_cached_full_stripes) >=
	    min(R5C_FULL_STRIPE_FLUSH_BATCH(conf),
		conf->chunk_sectors >> STRIPE_SHIFT))
		r5l_wake_reclaim(conf->log, 0);
}