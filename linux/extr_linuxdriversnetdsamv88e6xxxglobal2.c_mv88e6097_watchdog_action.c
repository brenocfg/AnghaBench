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
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IRQ_HANDLED ; 
 int /*<<< orphan*/  MV88E6352_G2_WDOG_CTL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv88e6xxx_g2_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mv88e6097_watchdog_action(struct mv88e6xxx_chip *chip, int irq)
{
	u16 reg;

	mv88e6xxx_g2_read(chip, MV88E6352_G2_WDOG_CTL, &reg);

	dev_info(chip->dev, "Watchdog event: 0x%04x", reg);

	return IRQ_HANDLED;
}