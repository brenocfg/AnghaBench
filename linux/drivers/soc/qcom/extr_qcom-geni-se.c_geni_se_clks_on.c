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
struct geni_wrapper {int /*<<< orphan*/  ahb_clks; } ;
struct geni_se {int /*<<< orphan*/  clk; struct geni_wrapper* wrapper; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_bulk_disable_unprepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_bulk_prepare_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int geni_se_clks_on(struct geni_se *se)
{
	int ret;
	struct geni_wrapper *wrapper = se->wrapper;

	ret = clk_bulk_prepare_enable(ARRAY_SIZE(wrapper->ahb_clks),
						wrapper->ahb_clks);
	if (ret)
		return ret;

	ret = clk_prepare_enable(se->clk);
	if (ret)
		clk_bulk_disable_unprepare(ARRAY_SIZE(wrapper->ahb_clks),
							wrapper->ahb_clks);
	return ret;
}