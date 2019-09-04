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
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 struct clk* clk_get (struct device*,char const*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 

__attribute__((used)) static void disable_clock(struct device *dev, const char *con_id)
{
	struct clk *clk;

	clk = clk_get(dev, con_id);
	if (!IS_ERR(clk)) {
		clk_disable_unprepare(clk);
		clk_put(clk);
		dev_info(dev, "Runtime PM disabled, clock forced off.\n");
	}
}