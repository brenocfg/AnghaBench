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
struct mlxreg_hotplug_priv_data {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dwork_irq; int /*<<< orphan*/  irq; TYPE_1__* pdev; } ;
struct mlxreg_core_item {int count; struct mlxreg_core_data* data; } ;
struct mlxreg_core_hotplug_platform_data {int counter; scalar_t__ cell; scalar_t__ cell_low; struct mlxreg_core_item* items; } ;
struct mlxreg_core_data {scalar_t__ reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MLXREG_HOTPLUG_AGGR_MASK_OFF ; 
 scalar_t__ MLXREG_HOTPLUG_EVENT_OFF ; 
 scalar_t__ MLXREG_HOTPLUG_MASK_OFF ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct mlxreg_core_hotplug_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxreg_hotplug_device_destroy (struct mlxreg_hotplug_priv_data*,struct mlxreg_core_data*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxreg_hotplug_unset_irq(struct mlxreg_hotplug_priv_data *priv)
{
	struct mlxreg_core_hotplug_platform_data *pdata;
	struct mlxreg_core_item *item;
	struct mlxreg_core_data *data;
	int count, i, j;

	pdata = dev_get_platdata(&priv->pdev->dev);
	item = pdata->items;
	disable_irq(priv->irq);
	cancel_delayed_work_sync(&priv->dwork_irq);

	/* Mask low aggregation event, if defined. */
	if (pdata->cell_low)
		regmap_write(priv->regmap, pdata->cell_low +
			     MLXREG_HOTPLUG_AGGR_MASK_OFF, 0);

	/* Mask aggregation event. */
	regmap_write(priv->regmap, pdata->cell + MLXREG_HOTPLUG_AGGR_MASK_OFF,
		     0);

	/* Clear topology configurations. */
	for (i = 0; i < pdata->counter; i++, item++) {
		data = item->data;
		/* Mask group presense event. */
		regmap_write(priv->regmap, data->reg + MLXREG_HOTPLUG_MASK_OFF,
			     0);
		/* Clear group presense event. */
		regmap_write(priv->regmap, data->reg +
			     MLXREG_HOTPLUG_EVENT_OFF, 0);

		/* Remove all the attached devices in group. */
		count = item->count;
		for (j = 0; j < count; j++, data++)
			mlxreg_hotplug_device_destroy(priv, data);
	}
}