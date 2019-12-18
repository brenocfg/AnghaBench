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
typedef  scalar_t__ u32 ;
struct resource {scalar_t__ start; } ;
struct qcom_smem {TYPE_1__* regions; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
struct TYPE_2__ {int /*<<< orphan*/  size; scalar_t__ aux_base; int /*<<< orphan*/  virt_base; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*) ; 
 int /*<<< orphan*/  devm_ioremap_wc (struct device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int qcom_smem_map_memory(struct qcom_smem *smem, struct device *dev,
				const char *name, int i)
{
	struct device_node *np;
	struct resource r;
	resource_size_t size;
	int ret;

	np = of_parse_phandle(dev->of_node, name, 0);
	if (!np) {
		dev_err(dev, "No %s specified\n", name);
		return -EINVAL;
	}

	ret = of_address_to_resource(np, 0, &r);
	of_node_put(np);
	if (ret)
		return ret;
	size = resource_size(&r);

	smem->regions[i].virt_base = devm_ioremap_wc(dev, r.start, size);
	if (!smem->regions[i].virt_base)
		return -ENOMEM;
	smem->regions[i].aux_base = (u32)r.start;
	smem->regions[i].size = size;

	return 0;
}