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
struct max17042_chip {int /*<<< orphan*/  battery; TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MAX17042_STATUS ; 
 int STATUS_INTR_SOCMAX_BIT ; 
 int STATUS_INTR_SOCMIN_BIT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  max17042_set_soc_threshold (struct max17042_chip*,int) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static irqreturn_t max17042_thread_handler(int id, void *dev)
{
	struct max17042_chip *chip = dev;
	u32 val;

	regmap_read(chip->regmap, MAX17042_STATUS, &val);
	if ((val & STATUS_INTR_SOCMIN_BIT) ||
		(val & STATUS_INTR_SOCMAX_BIT)) {
		dev_info(&chip->client->dev, "SOC threshold INTR\n");
		max17042_set_soc_threshold(chip, 1);
	}

	power_supply_changed(chip->battery);
	return IRQ_HANDLED;
}