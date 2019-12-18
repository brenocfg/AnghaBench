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
struct rcar_lvds {int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct clk *rcar_lvds_get_clock(struct rcar_lvds *lvds, const char *name,
				       bool optional)
{
	struct clk *clk;

	clk = devm_clk_get(lvds->dev, name);
	if (!IS_ERR(clk))
		return clk;

	if (PTR_ERR(clk) == -ENOENT && optional)
		return NULL;

	if (PTR_ERR(clk) != -EPROBE_DEFER)
		dev_err(lvds->dev, "failed to get %s clock\n",
			name ? name : "module");

	return clk;
}