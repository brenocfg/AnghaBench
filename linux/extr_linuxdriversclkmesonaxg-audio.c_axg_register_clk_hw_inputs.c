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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int axg_register_clk_hw_input (struct device*,char*,unsigned int) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 

__attribute__((used)) static int axg_register_clk_hw_inputs(struct device *dev,
				      const char *basename,
				      unsigned int count,
				      unsigned int clkid)
{
	char *name;
	int i, ret;

	for (i = 0; i < count; i++) {
		name = kasprintf(GFP_KERNEL, "%s%d", basename, i);
		if (!name)
			return -ENOMEM;

		ret = axg_register_clk_hw_input(dev, name, clkid + i);
		kfree(name);
		if (ret)
			return ret;
	}

	return 0;
}