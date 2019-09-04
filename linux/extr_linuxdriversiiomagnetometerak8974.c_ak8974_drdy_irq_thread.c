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
struct ak8974 {int /*<<< orphan*/  drdy_complete; TYPE_1__* i2c; int /*<<< orphan*/  map; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK8974_STATUS ; 
 unsigned int AK8974_STATUS_DRDY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static irqreturn_t ak8974_drdy_irq_thread(int irq, void *d)
{
	struct ak8974 *ak8974 = d;
	unsigned int val;
	int ret;

	/* Check if this was a DRDY from us */
	ret = regmap_read(ak8974->map, AK8974_STATUS, &val);
	if (ret < 0) {
		dev_err(&ak8974->i2c->dev, "error reading DRDY status\n");
		return IRQ_HANDLED;
	}
	if (val & AK8974_STATUS_DRDY) {
		/* Yes this was our IRQ */
		complete(&ak8974->drdy_complete);
		return IRQ_HANDLED;
	}

	/* We may be on a shared IRQ, let the next client check */
	return IRQ_NONE;
}