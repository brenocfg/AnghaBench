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
typedef  int u32 ;
struct sysc {int /*<<< orphan*/  module_size; int /*<<< orphan*/  module_pa; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,struct device_node*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  of_translate_address (struct device_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sysc_parse_and_check_child_range(struct sysc *ddata)
{
	struct device_node *np = ddata->dev->of_node;
	const __be32 *ranges;
	u32 nr_addr, nr_size;
	int len, error;

	ranges = of_get_property(np, "ranges", &len);
	if (!ranges) {
		dev_err(ddata->dev, "missing ranges for %pOF\n", np);

		return -ENOENT;
	}

	len /= sizeof(*ranges);

	if (len < 3) {
		dev_err(ddata->dev, "incomplete ranges for %pOF\n", np);

		return -EINVAL;
	}

	error = of_property_read_u32(np, "#address-cells", &nr_addr);
	if (error)
		return -ENOENT;

	error = of_property_read_u32(np, "#size-cells", &nr_size);
	if (error)
		return -ENOENT;

	if (nr_addr != 1 || nr_size != 1) {
		dev_err(ddata->dev, "invalid ranges for %pOF\n", np);

		return -EINVAL;
	}

	ranges++;
	ddata->module_pa = of_translate_address(np, ranges++);
	ddata->module_size = be32_to_cpup(ranges);

	return 0;
}