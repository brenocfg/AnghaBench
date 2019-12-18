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
struct r5conf {int /*<<< orphan*/  empty_inactive_list_nr; scalar_t__ quiesce; int /*<<< orphan*/  cache_state; } ;
struct mddev {struct r5conf* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  R5C_LOG_TIGHT ; 
 int /*<<< orphan*/  R5_INACTIVE_BLOCKED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int raid5_congested(struct mddev *mddev, int bits)
{
	struct r5conf *conf = mddev->private;

	/* No difference between reads and writes.  Just check
	 * how busy the stripe_cache is
	 */

	if (test_bit(R5_INACTIVE_BLOCKED, &conf->cache_state))
		return 1;

	/* Also checks whether there is pressure on r5cache log space */
	if (test_bit(R5C_LOG_TIGHT, &conf->cache_state))
		return 1;
	if (conf->quiesce)
		return 1;
	if (atomic_read(&conf->empty_inactive_list_nr))
		return 1;

	return 0;
}