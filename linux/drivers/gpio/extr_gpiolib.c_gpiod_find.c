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
struct gpiod_lookup_table {struct gpiod_lookup* table; } ;
struct gpiod_lookup {unsigned int idx; unsigned long flags; int /*<<< orphan*/  chip_hwnum; scalar_t__ chip_label; scalar_t__ con_id; } ;
struct gpio_desc {int dummy; } ;
struct gpio_chip {int /*<<< orphan*/  label; int /*<<< orphan*/  ngpio; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct gpio_desc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,scalar_t__) ; 
 struct gpio_chip* find_chip_by_name (scalar_t__) ; 
 struct gpio_desc* gpiochip_get_desc (struct gpio_chip*,int /*<<< orphan*/ ) ; 
 struct gpiod_lookup_table* gpiod_find_lookup_table (struct device*) ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static struct gpio_desc *gpiod_find(struct device *dev, const char *con_id,
				    unsigned int idx, unsigned long *flags)
{
	struct gpio_desc *desc = ERR_PTR(-ENOENT);
	struct gpiod_lookup_table *table;
	struct gpiod_lookup *p;

	table = gpiod_find_lookup_table(dev);
	if (!table)
		return desc;

	for (p = &table->table[0]; p->chip_label; p++) {
		struct gpio_chip *chip;

		/* idx must always match exactly */
		if (p->idx != idx)
			continue;

		/* If the lookup entry has a con_id, require exact match */
		if (p->con_id && (!con_id || strcmp(p->con_id, con_id)))
			continue;

		chip = find_chip_by_name(p->chip_label);

		if (!chip) {
			/*
			 * As the lookup table indicates a chip with
			 * p->chip_label should exist, assume it may
			 * still appear later and let the interested
			 * consumer be probed again or let the Deferred
			 * Probe infrastructure handle the error.
			 */
			dev_warn(dev, "cannot find GPIO chip %s, deferring\n",
				 p->chip_label);
			return ERR_PTR(-EPROBE_DEFER);
		}

		if (chip->ngpio <= p->chip_hwnum) {
			dev_err(dev,
				"requested GPIO %d is out of range [0..%d] for chip %s\n",
				idx, chip->ngpio, chip->label);
			return ERR_PTR(-EINVAL);
		}

		desc = gpiochip_get_desc(chip, p->chip_hwnum);
		*flags = p->flags;

		return desc;
	}

	return desc;
}