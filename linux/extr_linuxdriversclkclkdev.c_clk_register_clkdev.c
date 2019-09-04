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
struct clk_lookup {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  __clk_get_hw (struct clk*) ; 
 struct clk_lookup* __clk_register_clkdev (int /*<<< orphan*/ ,char const*,char*,...) ; 

int clk_register_clkdev(struct clk *clk, const char *con_id,
	const char *dev_id)
{
	struct clk_lookup *cl;

	if (IS_ERR(clk))
		return PTR_ERR(clk);

	/*
	 * Since dev_id can be NULL, and NULL is handled specially, we must
	 * pass it as either a NULL format string, or with "%s".
	 */
	if (dev_id)
		cl = __clk_register_clkdev(__clk_get_hw(clk), con_id, "%s",
					   dev_id);
	else
		cl = __clk_register_clkdev(__clk_get_hw(clk), con_id, NULL);

	return cl ? 0 : -ENOMEM;
}