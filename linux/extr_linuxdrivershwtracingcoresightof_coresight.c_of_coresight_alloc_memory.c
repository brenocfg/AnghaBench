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
struct coresight_platform_data {void* child_ports; int /*<<< orphan*/  nr_outport; void* child_names; void* outports; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* devm_kcalloc (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int of_coresight_alloc_memory(struct device *dev,
			struct coresight_platform_data *pdata)
{
	/* List of output port on this component */
	pdata->outports = devm_kcalloc(dev,
				       pdata->nr_outport,
				       sizeof(*pdata->outports),
				       GFP_KERNEL);
	if (!pdata->outports)
		return -ENOMEM;

	/* Children connected to this component via @outports */
	pdata->child_names = devm_kcalloc(dev,
					  pdata->nr_outport,
					  sizeof(*pdata->child_names),
					  GFP_KERNEL);
	if (!pdata->child_names)
		return -ENOMEM;

	/* Port number on the child this component is connected to */
	pdata->child_ports = devm_kcalloc(dev,
					  pdata->nr_outport,
					  sizeof(*pdata->child_ports),
					  GFP_KERNEL);
	if (!pdata->child_ports)
		return -ENOMEM;

	return 0;
}