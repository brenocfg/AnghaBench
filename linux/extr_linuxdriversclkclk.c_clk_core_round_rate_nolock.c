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
struct clk_rate_request {scalar_t__ rate; } ;
struct clk_core {int flags; scalar_t__ rate; struct clk_core* parent; } ;

/* Variables and functions */
 int CLK_SET_RATE_PARENT ; 
 scalar_t__ clk_core_can_round (struct clk_core*) ; 
 int clk_core_determine_round_nolock (struct clk_core*,struct clk_rate_request*) ; 
 int /*<<< orphan*/  clk_core_init_rate_req (struct clk_core*,struct clk_rate_request*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_lock ; 

__attribute__((used)) static int clk_core_round_rate_nolock(struct clk_core *core,
				      struct clk_rate_request *req)
{
	lockdep_assert_held(&prepare_lock);

	if (!core) {
		req->rate = 0;
		return 0;
	}

	clk_core_init_rate_req(core, req);

	if (clk_core_can_round(core))
		return clk_core_determine_round_nolock(core, req);
	else if (core->flags & CLK_SET_RATE_PARENT)
		return clk_core_round_rate_nolock(core->parent, req);

	req->rate = core->rate;
	return 0;
}