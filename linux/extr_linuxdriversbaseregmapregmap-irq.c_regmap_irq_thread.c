#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct regmap_irq_chip_data {int irq_reg_stride; int* status_reg_buf; int* status_buf; int* mask_buf; int /*<<< orphan*/  domain; struct regmap_irq_chip* chip; struct regmap* map; } ;
struct regmap_irq_chip {int num_regs; int ack_base; int num_irqs; int /*<<< orphan*/  irq_drv_data; int /*<<< orphan*/  (* handle_post_irq ) (int /*<<< orphan*/ ) ;scalar_t__ runtime_pm; TYPE_2__* irqs; scalar_t__ use_ack; scalar_t__ status_base; int /*<<< orphan*/  (* handle_pre_irq ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int val_bytes; } ;
struct regmap {int reg_stride; int /*<<< orphan*/  dev; TYPE_1__ format; int /*<<< orphan*/  use_single_read; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {size_t reg_offset; int mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  handle_nested_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int regmap_bulk_read (struct regmap*,scalar_t__,int*,int) ; 
 int regmap_read (struct regmap*,scalar_t__,int*) ; 
 int regmap_write (struct regmap*,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t regmap_irq_thread(int irq, void *d)
{
	struct regmap_irq_chip_data *data = d;
	const struct regmap_irq_chip *chip = data->chip;
	struct regmap *map = data->map;
	int ret, i;
	bool handled = false;
	u32 reg;

	if (chip->handle_pre_irq)
		chip->handle_pre_irq(chip->irq_drv_data);

	if (chip->runtime_pm) {
		ret = pm_runtime_get_sync(map->dev);
		if (ret < 0) {
			dev_err(map->dev, "IRQ thread failed to resume: %d\n",
				ret);
			pm_runtime_put(map->dev);
			goto exit;
		}
	}

	/*
	 * Read in the statuses, using a single bulk read if possible
	 * in order to reduce the I/O overheads.
	 */
	if (!map->use_single_read && map->reg_stride == 1 &&
	    data->irq_reg_stride == 1) {
		u8 *buf8 = data->status_reg_buf;
		u16 *buf16 = data->status_reg_buf;
		u32 *buf32 = data->status_reg_buf;

		BUG_ON(!data->status_reg_buf);

		ret = regmap_bulk_read(map, chip->status_base,
				       data->status_reg_buf,
				       chip->num_regs);
		if (ret != 0) {
			dev_err(map->dev, "Failed to read IRQ status: %d\n",
				ret);
			goto exit;
		}

		for (i = 0; i < data->chip->num_regs; i++) {
			switch (map->format.val_bytes) {
			case 1:
				data->status_buf[i] = buf8[i];
				break;
			case 2:
				data->status_buf[i] = buf16[i];
				break;
			case 4:
				data->status_buf[i] = buf32[i];
				break;
			default:
				BUG();
				goto exit;
			}
		}

	} else {
		for (i = 0; i < data->chip->num_regs; i++) {
			ret = regmap_read(map, chip->status_base +
					  (i * map->reg_stride
					   * data->irq_reg_stride),
					  &data->status_buf[i]);

			if (ret != 0) {
				dev_err(map->dev,
					"Failed to read IRQ status: %d\n",
					ret);
				if (chip->runtime_pm)
					pm_runtime_put(map->dev);
				goto exit;
			}
		}
	}

	/*
	 * Ignore masked IRQs and ack if we need to; we ack early so
	 * there is no race between handling and acknowleding the
	 * interrupt.  We assume that typically few of the interrupts
	 * will fire simultaneously so don't worry about overhead from
	 * doing a write per register.
	 */
	for (i = 0; i < data->chip->num_regs; i++) {
		data->status_buf[i] &= ~data->mask_buf[i];

		if (data->status_buf[i] && (chip->ack_base || chip->use_ack)) {
			reg = chip->ack_base +
				(i * map->reg_stride * data->irq_reg_stride);
			ret = regmap_write(map, reg, data->status_buf[i]);
			if (ret != 0)
				dev_err(map->dev, "Failed to ack 0x%x: %d\n",
					reg, ret);
		}
	}

	for (i = 0; i < chip->num_irqs; i++) {
		if (data->status_buf[chip->irqs[i].reg_offset /
				     map->reg_stride] & chip->irqs[i].mask) {
			handle_nested_irq(irq_find_mapping(data->domain, i));
			handled = true;
		}
	}

	if (chip->runtime_pm)
		pm_runtime_put(map->dev);

exit:
	if (chip->handle_post_irq)
		chip->handle_post_irq(chip->irq_drv_data);

	if (handled)
		return IRQ_HANDLED;
	else
		return IRQ_NONE;
}