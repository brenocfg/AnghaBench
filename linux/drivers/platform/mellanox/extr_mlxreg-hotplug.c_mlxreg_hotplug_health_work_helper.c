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
struct mlxreg_hotplug_priv_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct mlxreg_core_item {int count; int /*<<< orphan*/  cache; struct mlxreg_core_data* data; } ;
struct mlxreg_core_data {int attached; int /*<<< orphan*/  mask; scalar_t__ reg; scalar_t__ health_cntr; } ;

/* Variables and functions */
 scalar_t__ MLXREG_HOTPLUG_EVENT_OFF ; 
 int /*<<< orphan*/  MLXREG_HOTPLUG_GOOD_HEALTH_MASK ; 
 scalar_t__ MLXREG_HOTPLUG_MASK_OFF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxreg_hotplug_device_create (struct mlxreg_hotplug_priv_data*,struct mlxreg_core_data*) ; 
 int /*<<< orphan*/  mlxreg_hotplug_device_destroy (struct mlxreg_hotplug_priv_data*,struct mlxreg_core_data*) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxreg_hotplug_health_work_helper(struct mlxreg_hotplug_priv_data *priv,
				  struct mlxreg_core_item *item)
{
	struct mlxreg_core_data *data = item->data;
	u32 regval;
	int i, ret = 0;

	for (i = 0; i < item->count; i++, data++) {
		/* Mask event. */
		ret = regmap_write(priv->regmap, data->reg +
				   MLXREG_HOTPLUG_MASK_OFF, 0);
		if (ret)
			goto out;

		/* Read status. */
		ret = regmap_read(priv->regmap, data->reg, &regval);
		if (ret)
			goto out;

		regval &= data->mask;

		if (item->cache == regval)
			goto ack_event;

		/*
		 * ASIC health indication is provided through two bits. Bits
		 * value 0x2 indicates that ASIC reached the good health, value
		 * 0x0 indicates ASIC the bad health or dormant state and value
		 * 0x3 indicates the booting state. During ASIC reset it should
		 * pass the following states: dormant -> booting -> good.
		 */
		if (regval == MLXREG_HOTPLUG_GOOD_HEALTH_MASK) {
			if (!data->attached) {
				/*
				 * ASIC is in steady state. Connect associated
				 * device, if configured.
				 */
				mlxreg_hotplug_device_create(priv, data);
				data->attached = true;
			}
		} else {
			if (data->attached) {
				/*
				 * ASIC health is failed after ASIC has been
				 * in steady state. Disconnect associated
				 * device, if it has been connected.
				 */
				mlxreg_hotplug_device_destroy(priv, data);
				data->attached = false;
				data->health_cntr = 0;
			}
		}
		item->cache = regval;
ack_event:
		/* Acknowledge event. */
		ret = regmap_write(priv->regmap, data->reg +
				   MLXREG_HOTPLUG_EVENT_OFF, 0);
		if (ret)
			goto out;

		/* Unmask event. */
		ret = regmap_write(priv->regmap, data->reg +
				   MLXREG_HOTPLUG_MASK_OFF, data->mask);
		if (ret)
			goto out;
	}

 out:
	if (ret)
		dev_err(priv->dev, "Failed to complete workqueue.\n");
}