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
struct tps6521x_pwrbutton {int /*<<< orphan*/  idev; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; struct tps6521x_data* data; } ;
struct tps6521x_data {unsigned int pb_mask; int /*<<< orphan*/  reg_status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_wakeup_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static irqreturn_t tps6521x_pb_irq(int irq, void *_pwr)
{
	struct tps6521x_pwrbutton *pwr = _pwr;
	const struct tps6521x_data *tps_data = pwr->data;
	unsigned int reg;
	int error;

	error = regmap_read(pwr->regmap, tps_data->reg_status, &reg);
	if (error) {
		dev_err(pwr->dev, "can't read register: %d\n", error);
		goto out;
	}

	if (reg & tps_data->pb_mask) {
		input_report_key(pwr->idev, KEY_POWER, 1);
		pm_wakeup_event(pwr->dev, 0);
	} else {
		input_report_key(pwr->idev, KEY_POWER, 0);
	}

	input_sync(pwr->idev);

out:
	return IRQ_HANDLED;
}