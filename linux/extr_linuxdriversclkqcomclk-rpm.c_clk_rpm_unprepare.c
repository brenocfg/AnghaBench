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
struct clk_rpm {int enabled; scalar_t__ branch; int /*<<< orphan*/  rate; struct clk_rpm* peer; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int clk_rpm_set_rate_active (struct clk_rpm*,unsigned long) ; 
 int clk_rpm_set_rate_sleep (struct clk_rpm*,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpm_clk_lock ; 
 int /*<<< orphan*/  to_active_sleep (struct clk_rpm*,int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 
 struct clk_rpm* to_clk_rpm (struct clk_hw*) ; 

__attribute__((used)) static void clk_rpm_unprepare(struct clk_hw *hw)
{
	struct clk_rpm *r = to_clk_rpm(hw);
	struct clk_rpm *peer = r->peer;
	unsigned long peer_rate = 0, peer_sleep_rate = 0;
	unsigned long active_rate, sleep_rate;
	int ret;

	mutex_lock(&rpm_clk_lock);

	if (!r->rate)
		goto out;

	/* Take peer clock's rate into account only if it's enabled. */
	if (peer->enabled)
		to_active_sleep(peer, peer->rate, &peer_rate,
				&peer_sleep_rate);

	active_rate = r->branch ? !!peer_rate : peer_rate;
	ret = clk_rpm_set_rate_active(r, active_rate);
	if (ret)
		goto out;

	sleep_rate = r->branch ? !!peer_sleep_rate : peer_sleep_rate;
	ret = clk_rpm_set_rate_sleep(r, sleep_rate);
	if (ret)
		goto out;

	r->enabled = false;

out:
	mutex_unlock(&rpm_clk_lock);
}