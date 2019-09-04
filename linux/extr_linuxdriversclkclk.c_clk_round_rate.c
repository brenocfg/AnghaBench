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
struct clk {int /*<<< orphan*/  core; scalar_t__ exclusive_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_core_get_boundaries (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_core_rate_protect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_core_rate_unprotect (int /*<<< orphan*/ ) ; 
 int clk_core_round_rate_nolock (int /*<<< orphan*/ ,struct clk_rate_request*) ; 
 int /*<<< orphan*/  clk_prepare_lock () ; 
 int /*<<< orphan*/  clk_prepare_unlock () ; 

long clk_round_rate(struct clk *clk, unsigned long rate)
{
	struct clk_rate_request req;
	int ret;

	if (!clk)
		return 0;

	clk_prepare_lock();

	if (clk->exclusive_count)
		clk_core_rate_unprotect(clk->core);

	clk_core_get_boundaries(clk->core, &req.min_rate, &req.max_rate);
	req.rate = rate;

	ret = clk_core_round_rate_nolock(clk->core, &req);

	if (clk->exclusive_count)
		clk_core_rate_protect(clk->core);

	clk_prepare_unlock();

	if (ret)
		return ret;

	return req.rate;
}