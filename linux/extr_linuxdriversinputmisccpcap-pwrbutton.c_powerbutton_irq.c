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
struct cpcap_power_button {int /*<<< orphan*/  idev; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int cpcap_sense_virq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_wakeup_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t powerbutton_irq(int irq, void *_button)
{
	struct cpcap_power_button *button = _button;
	int val;

	val = cpcap_sense_virq(button->regmap, irq);
	if (val < 0) {
		dev_err(button->dev, "irq read failed: %d", val);
		return IRQ_HANDLED;
	}

	pm_wakeup_event(button->dev, 0);
	input_report_key(button->idev, KEY_POWER, val);
	input_sync(button->idev);

	return IRQ_HANDLED;
}