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
struct r5conf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRIPE_BATCH_READY ; 
 int /*<<< orphan*/  STRIPE_BITMAP_PENDING ; 
 scalar_t__ is_full_stripe_write (struct stripe_head*) ; 
 scalar_t__ raid5_has_log (struct r5conf*) ; 
 scalar_t__ raid5_has_ppl (struct r5conf*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool stripe_can_batch(struct stripe_head *sh)
{
	struct r5conf *conf = sh->raid_conf;

	if (raid5_has_log(conf) || raid5_has_ppl(conf))
		return false;
	return test_bit(STRIPE_BATCH_READY, &sh->state) &&
		!test_bit(STRIPE_BITMAP_PENDING, &sh->state) &&
		is_full_stripe_write(sh);
}