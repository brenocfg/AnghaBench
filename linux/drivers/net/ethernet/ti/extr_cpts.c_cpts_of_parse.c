#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct device_node {int dummy; } ;
struct TYPE_2__ {void* shift; void* mult; } ;
struct cpts {int /*<<< orphan*/  dev; TYPE_1__ cc; } ;

/* Variables and functions */
 int EINVAL ; 
 int cpts_of_mux_clk_setup (struct cpts*,struct device_node*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,void**) ; 

__attribute__((used)) static int cpts_of_parse(struct cpts *cpts, struct device_node *node)
{
	int ret = -EINVAL;
	u32 prop;

	if (!of_property_read_u32(node, "cpts_clock_mult", &prop))
		cpts->cc.mult = prop;

	if (!of_property_read_u32(node, "cpts_clock_shift", &prop))
		cpts->cc.shift = prop;

	if ((cpts->cc.mult && !cpts->cc.shift) ||
	    (!cpts->cc.mult && cpts->cc.shift))
		goto of_error;

	return cpts_of_mux_clk_setup(cpts, node);

of_error:
	dev_err(cpts->dev, "CPTS: Missing property in the DT.\n");
	return ret;
}