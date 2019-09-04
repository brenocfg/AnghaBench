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
struct input_dev {int dummy; } ;
struct axp20x_pek {int irq_dbf; int irq_dbr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  KEY_POWER ; 
 struct axp20x_pek* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static irqreturn_t axp20x_pek_irq(int irq, void *pwr)
{
	struct input_dev *idev = pwr;
	struct axp20x_pek *axp20x_pek = input_get_drvdata(idev);

	/*
	 * The power-button is connected to ground so a falling edge (dbf)
	 * means it is pressed.
	 */
	if (irq == axp20x_pek->irq_dbf)
		input_report_key(idev, KEY_POWER, true);
	else if (irq == axp20x_pek->irq_dbr)
		input_report_key(idev, KEY_POWER, false);

	input_sync(idev);

	return IRQ_HANDLED;
}