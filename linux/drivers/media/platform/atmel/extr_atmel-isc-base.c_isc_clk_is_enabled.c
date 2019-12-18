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
typedef  int u32 ;
struct isc_clk {scalar_t__ id; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int ISC_CLK (scalar_t__) ; 
 int /*<<< orphan*/  ISC_CLKSR ; 
 scalar_t__ ISC_ISPCK ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct isc_clk* to_isc_clk (struct clk_hw*) ; 

__attribute__((used)) static int isc_clk_is_enabled(struct clk_hw *hw)
{
	struct isc_clk *isc_clk = to_isc_clk(hw);
	u32 status;

	if (isc_clk->id == ISC_ISPCK)
		pm_runtime_get_sync(isc_clk->dev);

	regmap_read(isc_clk->regmap, ISC_CLKSR, &status);

	if (isc_clk->id == ISC_ISPCK)
		pm_runtime_put_sync(isc_clk->dev);

	return status & ISC_CLK(isc_clk->id) ? 1 : 0;
}