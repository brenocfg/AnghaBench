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
struct isc_clk {scalar_t__ id; int /*<<< orphan*/  dev; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ ISC_ISPCK ; 
 int /*<<< orphan*/  isc_wait_clk_stable (struct clk_hw*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 struct isc_clk* to_isc_clk (struct clk_hw*) ; 

__attribute__((used)) static void isc_clk_unprepare(struct clk_hw *hw)
{
	struct isc_clk *isc_clk = to_isc_clk(hw);

	isc_wait_clk_stable(hw);

	if (isc_clk->id == ISC_ISPCK)
		pm_runtime_put_sync(isc_clk->dev);
}