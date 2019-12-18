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
struct da906x_chip_config {unsigned int onkey_nonkey_mask; int /*<<< orphan*/  onkey_status; } ;
struct da9063_onkey {int /*<<< orphan*/  dev; int /*<<< orphan*/  input; int /*<<< orphan*/  work; scalar_t__ key_power; int /*<<< orphan*/  regmap; struct da906x_chip_config* config; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t da9063_onkey_irq_handler(int irq, void *data)
{
	struct da9063_onkey *onkey = data;
	const struct da906x_chip_config *config = onkey->config;
	unsigned int val;
	int error;

	error = regmap_read(onkey->regmap,
			    config->onkey_status,
			    &val);
	if (onkey->key_power && !error && (val & config->onkey_nonkey_mask)) {
		input_report_key(onkey->input, KEY_POWER, 1);
		input_sync(onkey->input);
		schedule_delayed_work(&onkey->work, 0);
		dev_dbg(onkey->dev, "KEY_POWER long press.\n");
	} else {
		input_report_key(onkey->input, KEY_POWER, 1);
		input_sync(onkey->input);
		input_report_key(onkey->input, KEY_POWER, 0);
		input_sync(onkey->input);
		dev_dbg(onkey->dev, "KEY_POWER short press.\n");
	}

	return IRQ_HANDLED;
}