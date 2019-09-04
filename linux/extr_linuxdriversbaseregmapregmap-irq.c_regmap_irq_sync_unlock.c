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
struct regmap_irq_chip_data {int irq_reg_stride; int type_reg_stride; int wake_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  irq; TYPE_1__* chip; struct regmap* map; int /*<<< orphan*/ * type_buf; int /*<<< orphan*/ * type_buf_def; int /*<<< orphan*/ * mask_buf; int /*<<< orphan*/ * wake_buf; int /*<<< orphan*/ * mask_buf_def; } ;
struct regmap {int reg_stride; int /*<<< orphan*/  dev; } ;
struct irq_data {int dummy; } ;
struct TYPE_2__ {int num_regs; int mask_base; int unmask_base; int wake_base; int ack_base; int num_type_reg; int type_base; scalar_t__ runtime_pm; scalar_t__ type_invert; scalar_t__ ack_invert; scalar_t__ use_ack; int /*<<< orphan*/  init_ack_masked; scalar_t__ wake_invert; scalar_t__ mask_invert; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 struct regmap_irq_chip_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_set_irq_wake (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int regmap_irq_update_bits (struct regmap_irq_chip_data*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (struct regmap*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void regmap_irq_sync_unlock(struct irq_data *data)
{
	struct regmap_irq_chip_data *d = irq_data_get_irq_chip_data(data);
	struct regmap *map = d->map;
	int i, ret;
	u32 reg;
	u32 unmask_offset;

	if (d->chip->runtime_pm) {
		ret = pm_runtime_get_sync(map->dev);
		if (ret < 0)
			dev_err(map->dev, "IRQ sync failed to resume: %d\n",
				ret);
	}

	/*
	 * If there's been a change in the mask write it back to the
	 * hardware.  We rely on the use of the regmap core cache to
	 * suppress pointless writes.
	 */
	for (i = 0; i < d->chip->num_regs; i++) {
		reg = d->chip->mask_base +
			(i * map->reg_stride * d->irq_reg_stride);
		if (d->chip->mask_invert) {
			ret = regmap_irq_update_bits(d, reg,
					 d->mask_buf_def[i], ~d->mask_buf[i]);
		} else if (d->chip->unmask_base) {
			/* set mask with mask_base register */
			ret = regmap_irq_update_bits(d, reg,
					d->mask_buf_def[i], ~d->mask_buf[i]);
			if (ret < 0)
				dev_err(d->map->dev,
					"Failed to sync unmasks in %x\n",
					reg);
			unmask_offset = d->chip->unmask_base -
							d->chip->mask_base;
			/* clear mask with unmask_base register */
			ret = regmap_irq_update_bits(d,
					reg + unmask_offset,
					d->mask_buf_def[i],
					d->mask_buf[i]);
		} else {
			ret = regmap_irq_update_bits(d, reg,
					 d->mask_buf_def[i], d->mask_buf[i]);
		}
		if (ret != 0)
			dev_err(d->map->dev, "Failed to sync masks in %x\n",
				reg);

		reg = d->chip->wake_base +
			(i * map->reg_stride * d->irq_reg_stride);
		if (d->wake_buf) {
			if (d->chip->wake_invert)
				ret = regmap_irq_update_bits(d, reg,
							 d->mask_buf_def[i],
							 ~d->wake_buf[i]);
			else
				ret = regmap_irq_update_bits(d, reg,
							 d->mask_buf_def[i],
							 d->wake_buf[i]);
			if (ret != 0)
				dev_err(d->map->dev,
					"Failed to sync wakes in %x: %d\n",
					reg, ret);
		}

		if (!d->chip->init_ack_masked)
			continue;
		/*
		 * Ack all the masked interrupts unconditionally,
		 * OR if there is masked interrupt which hasn't been Acked,
		 * it'll be ignored in irq handler, then may introduce irq storm
		 */
		if (d->mask_buf[i] && (d->chip->ack_base || d->chip->use_ack)) {
			reg = d->chip->ack_base +
				(i * map->reg_stride * d->irq_reg_stride);
			/* some chips ack by write 0 */
			if (d->chip->ack_invert)
				ret = regmap_write(map, reg, ~d->mask_buf[i]);
			else
				ret = regmap_write(map, reg, d->mask_buf[i]);
			if (ret != 0)
				dev_err(d->map->dev, "Failed to ack 0x%x: %d\n",
					reg, ret);
		}
	}

	for (i = 0; i < d->chip->num_type_reg; i++) {
		if (!d->type_buf_def[i])
			continue;
		reg = d->chip->type_base +
			(i * map->reg_stride * d->type_reg_stride);
		if (d->chip->type_invert)
			ret = regmap_irq_update_bits(d, reg,
				d->type_buf_def[i], ~d->type_buf[i]);
		else
			ret = regmap_irq_update_bits(d, reg,
				d->type_buf_def[i], d->type_buf[i]);
		if (ret != 0)
			dev_err(d->map->dev, "Failed to sync type in %x\n",
				reg);
	}

	if (d->chip->runtime_pm)
		pm_runtime_put(map->dev);

	/* If we've changed our wakeup count propagate it to the parent */
	if (d->wake_count < 0)
		for (i = d->wake_count; i < 0; i++)
			irq_set_irq_wake(d->irq, 0);
	else if (d->wake_count > 0)
		for (i = 0; i < d->wake_count; i++)
			irq_set_irq_wake(d->irq, 1);

	d->wake_count = 0;

	mutex_unlock(&d->lock);
}