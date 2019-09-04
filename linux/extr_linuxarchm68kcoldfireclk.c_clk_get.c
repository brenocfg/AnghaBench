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
struct clk {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 char const* dev_name (struct device*) ; 
 struct clk** mcf_clks ; 
 int /*<<< orphan*/  pr_warn (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

struct clk *clk_get(struct device *dev, const char *id)
{
	const char *clk_name = dev ? dev_name(dev) : id ? id : NULL;
	struct clk *clk;
	unsigned i;

	for (i = 0; (clk = mcf_clks[i]) != NULL; ++i)
		if (!strcmp(clk->name, clk_name))
			return clk;
	pr_warn("clk_get: didn't find clock %s\n", clk_name);
	return ERR_PTR(-ENOENT);
}