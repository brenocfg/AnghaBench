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
struct ts4800_ts {int pendown; int /*<<< orphan*/  dev; int /*<<< orphan*/  bit; int /*<<< orphan*/  reg; int /*<<< orphan*/  regmap; int /*<<< orphan*/  debounce; } ;
struct input_polled_dev {struct ts4800_ts* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBOUNCE_COUNT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ts4800_ts_open(struct input_polled_dev *dev)
{
	struct ts4800_ts *ts = dev->private;
	int ret;

	ts->pendown = false;
	ts->debounce = DEBOUNCE_COUNT;

	ret = regmap_update_bits(ts->regmap, ts->reg, ts->bit, ts->bit);
	if (ret)
		dev_warn(ts->dev, "Failed to enable touchscreen\n");
}