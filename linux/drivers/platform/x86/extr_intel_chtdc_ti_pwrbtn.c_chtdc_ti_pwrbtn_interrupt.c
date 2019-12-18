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
struct regmap {int dummy; } ;
struct TYPE_2__ {struct device* parent; } ;
struct input_dev {TYPE_1__ dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHTDC_TI_SIRQ_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int SIRQ_PWRBTN_REL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 struct regmap* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static irqreturn_t chtdc_ti_pwrbtn_interrupt(int irq, void *dev_id)
{
	struct input_dev *input = dev_id;
	struct device *dev = input->dev.parent;
	struct regmap *regmap = dev_get_drvdata(dev);
	int state;

	if (!regmap_read(regmap, CHTDC_TI_SIRQ_REG, &state)) {
		dev_dbg(dev, "SIRQ_REG=0x%x\n", state);
		input_report_key(input, KEY_POWER, !(state & SIRQ_PWRBTN_REL));
		input_sync(input);
	}

	return IRQ_HANDLED;
}