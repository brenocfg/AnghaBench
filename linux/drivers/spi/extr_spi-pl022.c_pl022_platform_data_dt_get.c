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
typedef  int /*<<< orphan*/  u32 ;
struct pl022_ssp_controller {int bus_id; int enable_dma; int /*<<< orphan*/  rt; int /*<<< orphan*/  autosuspend_delay; int /*<<< orphan*/  num_chipselect; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct pl022_ssp_controller* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pl022_ssp_controller *
pl022_platform_data_dt_get(struct device *dev)
{
	struct device_node *np = dev->of_node;
	struct pl022_ssp_controller *pd;
	u32 tmp = 0;

	if (!np) {
		dev_err(dev, "no dt node defined\n");
		return NULL;
	}

	pd = devm_kzalloc(dev, sizeof(struct pl022_ssp_controller), GFP_KERNEL);
	if (!pd)
		return NULL;

	pd->bus_id = -1;
	pd->enable_dma = 1;
	of_property_read_u32(np, "num-cs", &tmp);
	pd->num_chipselect = tmp;
	of_property_read_u32(np, "pl022,autosuspend-delay",
			     &pd->autosuspend_delay);
	pd->rt = of_property_read_bool(np, "pl022,rt");

	return pd;
}