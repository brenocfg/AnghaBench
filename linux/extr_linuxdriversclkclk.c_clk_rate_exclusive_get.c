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
struct clk {int /*<<< orphan*/  exclusive_count; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_core_rate_protect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_lock () ; 
 int /*<<< orphan*/  clk_prepare_unlock () ; 

int clk_rate_exclusive_get(struct clk *clk)
{
	if (!clk)
		return 0;

	clk_prepare_lock();
	clk_core_rate_protect(clk->core);
	clk->exclusive_count++;
	clk_prepare_unlock();

	return 0;
}