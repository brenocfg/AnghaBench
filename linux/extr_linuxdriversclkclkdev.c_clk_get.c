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
struct device {scalar_t__ of_node; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  PTR_ERR (struct clk*) ; 
 struct clk* __of_clk_get_by_name (scalar_t__,char const*,char const*) ; 
 struct clk* clk_get_sys (char const*,char const*) ; 
 char* dev_name (struct device*) ; 

struct clk *clk_get(struct device *dev, const char *con_id)
{
	const char *dev_id = dev ? dev_name(dev) : NULL;
	struct clk *clk;

	if (dev && dev->of_node) {
		clk = __of_clk_get_by_name(dev->of_node, dev_id, con_id);
		if (!IS_ERR(clk) || PTR_ERR(clk) == -EPROBE_DEFER)
			return clk;
	}

	return clk_get_sys(dev_id, con_id);
}