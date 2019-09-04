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
 int /*<<< orphan*/  ENOENT ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct clk bus_clk ; 
 struct clk cpu_clk ; 
 struct clk dsp_clk ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 struct clk vbus_clk ; 

struct clk *clk_get(struct device *dev, const char *id)
{
	if (!strcmp(id, "bus"))
		return &bus_clk;
	/* cpmac and vbus share the same rate */
	if (!strcmp(id, "cpmac"))
		return &vbus_clk;
	if (!strcmp(id, "cpu"))
		return &cpu_clk;
	if (!strcmp(id, "dsp"))
		return &dsp_clk;
	if (!strcmp(id, "vbus"))
		return &vbus_clk;
	return ERR_PTR(-ENOENT);
}