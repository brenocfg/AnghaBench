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
struct clk_rate_request {unsigned long rate; int /*<<< orphan*/  max_rate; int /*<<< orphan*/  min_rate; } ;
struct clk_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_core_get_boundaries (struct clk_core*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int clk_core_rate_nuke_protect (struct clk_core*) ; 
 int /*<<< orphan*/  clk_core_rate_restore_protect (struct clk_core*,int) ; 
 int clk_core_round_rate_nolock (struct clk_core*,struct clk_rate_request*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_lock ; 

__attribute__((used)) static unsigned long clk_core_req_round_rate_nolock(struct clk_core *core,
						     unsigned long req_rate)
{
	int ret, cnt;
	struct clk_rate_request req;

	lockdep_assert_held(&prepare_lock);

	if (!core)
		return 0;

	/* simulate what the rate would be if it could be freely set */
	cnt = clk_core_rate_nuke_protect(core);
	if (cnt < 0)
		return cnt;

	clk_core_get_boundaries(core, &req.min_rate, &req.max_rate);
	req.rate = req_rate;

	ret = clk_core_round_rate_nolock(core, &req);

	/* restore the protection */
	clk_core_rate_restore_protect(core, cnt);

	return ret ? 0 : req.rate;
}