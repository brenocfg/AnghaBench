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
struct clk_lookup {int /*<<< orphan*/  clk_hw; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 struct clk* __clk_create_clk (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  __clk_free_clk (struct clk*) ; 
 int /*<<< orphan*/  __clk_get (struct clk*) ; 
 struct clk_lookup* clk_find (char const*,char const*) ; 
 int /*<<< orphan*/  clocks_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct clk *clk_get_sys(const char *dev_id, const char *con_id)
{
	struct clk_lookup *cl;
	struct clk *clk = NULL;

	mutex_lock(&clocks_mutex);

	cl = clk_find(dev_id, con_id);
	if (!cl)
		goto out;

	clk = __clk_create_clk(cl->clk_hw, dev_id, con_id);
	if (IS_ERR(clk))
		goto out;

	if (!__clk_get(clk)) {
		__clk_free_clk(clk);
		cl = NULL;
		goto out;
	}

out:
	mutex_unlock(&clocks_mutex);

	return cl ? clk : ERR_PTR(-ENOENT);
}