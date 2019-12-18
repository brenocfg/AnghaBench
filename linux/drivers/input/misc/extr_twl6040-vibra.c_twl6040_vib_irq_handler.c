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
struct vibra_info {int /*<<< orphan*/  dev; struct twl6040* twl6040; } ;
struct twl6040 {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TWL6040_REG_STATUS ; 
 int /*<<< orphan*/  TWL6040_REG_VIBCTLL ; 
 int /*<<< orphan*/  TWL6040_REG_VIBCTLR ; 
 int /*<<< orphan*/  TWL6040_VIBENA ; 
 int TWL6040_VIBLOCDET ; 
 int TWL6040_VIBROCDET ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  twl6040_clear_bits (struct twl6040*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int twl6040_reg_read (struct twl6040*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t twl6040_vib_irq_handler(int irq, void *data)
{
	struct vibra_info *info = data;
	struct twl6040 *twl6040 = info->twl6040;
	u8 status;

	status = twl6040_reg_read(twl6040, TWL6040_REG_STATUS);
	if (status & TWL6040_VIBLOCDET) {
		dev_warn(info->dev, "Left Vibrator overcurrent detected\n");
		twl6040_clear_bits(twl6040, TWL6040_REG_VIBCTLL,
				   TWL6040_VIBENA);
	}
	if (status & TWL6040_VIBROCDET) {
		dev_warn(info->dev, "Right Vibrator overcurrent detected\n");
		twl6040_clear_bits(twl6040, TWL6040_REG_VIBCTLR,
				   TWL6040_VIBENA);
	}

	return IRQ_HANDLED;
}