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
typedef  int u8 ;
struct twl6040 {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TWL6040_REG_STATUS ; 
 int TWL6040_TSHUTDET ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  twl6040_power (struct twl6040*,int) ; 
 int twl6040_reg_read (struct twl6040*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t twl6040_thint_handler(int irq, void *data)
{
	struct twl6040 *twl6040 = data;
	u8 status;

	status = twl6040_reg_read(twl6040, TWL6040_REG_STATUS);
	if (status & TWL6040_TSHUTDET) {
		dev_warn(twl6040->dev, "Thermal shutdown, powering-off");
		twl6040_power(twl6040, 0);
	} else {
		dev_warn(twl6040->dev, "Leaving thermal shutdown, powering-on");
		twl6040_power(twl6040, 1);
	}

	return IRQ_HANDLED;
}