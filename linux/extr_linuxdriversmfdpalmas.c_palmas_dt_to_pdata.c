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
struct palmas_platform_data {int mux_from_pdata; int power_ctrl; int /*<<< orphan*/  pm_off; void* pad2; void* pad1; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct i2c_client {scalar_t__ irq; TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int PALMAS_POWER_CTRL_ENABLE1_MASK ; 
 int PALMAS_POWER_CTRL_ENABLE2_MASK ; 
 int PALMAS_POWER_CTRL_NSLEEP_MASK ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,void**) ; 
 int /*<<< orphan*/  palmas_set_pdata_irq_flag (struct i2c_client*,struct palmas_platform_data*) ; 

__attribute__((used)) static void palmas_dt_to_pdata(struct i2c_client *i2c,
		struct palmas_platform_data *pdata)
{
	struct device_node *node = i2c->dev.of_node;
	int ret;
	u32 prop;

	ret = of_property_read_u32(node, "ti,mux-pad1", &prop);
	if (!ret) {
		pdata->mux_from_pdata = 1;
		pdata->pad1 = prop;
	}

	ret = of_property_read_u32(node, "ti,mux-pad2", &prop);
	if (!ret) {
		pdata->mux_from_pdata = 1;
		pdata->pad2 = prop;
	}

	/* The default for this register is all masked */
	ret = of_property_read_u32(node, "ti,power-ctrl", &prop);
	if (!ret)
		pdata->power_ctrl = prop;
	else
		pdata->power_ctrl = PALMAS_POWER_CTRL_NSLEEP_MASK |
					PALMAS_POWER_CTRL_ENABLE1_MASK |
					PALMAS_POWER_CTRL_ENABLE2_MASK;
	if (i2c->irq)
		palmas_set_pdata_irq_flag(i2c, pdata);

	pdata->pm_off = of_property_read_bool(node,
			"ti,system-power-controller");
}