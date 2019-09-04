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
struct cht_wc_extcon_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHT_WC_PWRSRC_IRQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  cht_wc_extcon_pwrsrc_event (struct cht_wc_extcon_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t cht_wc_extcon_isr(int irq, void *data)
{
	struct cht_wc_extcon_data *ext = data;
	int ret, irqs;

	ret = regmap_read(ext->regmap, CHT_WC_PWRSRC_IRQ, &irqs);
	if (ret) {
		dev_err(ext->dev, "Error reading irqs: %d\n", ret);
		return IRQ_NONE;
	}

	cht_wc_extcon_pwrsrc_event(ext);

	ret = regmap_write(ext->regmap, CHT_WC_PWRSRC_IRQ, irqs);
	if (ret) {
		dev_err(ext->dev, "Error writing irqs: %d\n", ret);
		return IRQ_NONE;
	}

	return IRQ_HANDLED;
}