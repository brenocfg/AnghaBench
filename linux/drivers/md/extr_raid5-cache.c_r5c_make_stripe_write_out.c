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
struct stripe_head {int /*<<< orphan*/  state; struct r5conf* raid_conf; } ;
struct r5l_log {int dummy; } ;
struct r5conf {int /*<<< orphan*/  preread_active_stripes; struct r5l_log* log; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  STRIPE_PREREAD_ACTIVE ; 
 int /*<<< orphan*/  STRIPE_R5C_CACHING ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r5c_is_writeback (struct r5l_log*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void r5c_make_stripe_write_out(struct stripe_head *sh)
{
	struct r5conf *conf = sh->raid_conf;
	struct r5l_log *log = conf->log;

	BUG_ON(!r5c_is_writeback(log));

	WARN_ON(!test_bit(STRIPE_R5C_CACHING, &sh->state));
	clear_bit(STRIPE_R5C_CACHING, &sh->state);

	if (!test_and_set_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
		atomic_inc(&conf->preread_active_stripes);
}