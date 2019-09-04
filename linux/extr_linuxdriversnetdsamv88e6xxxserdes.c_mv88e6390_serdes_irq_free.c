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
struct mv88e6xxx_chip {TYPE_1__* ports; int /*<<< orphan*/  reg_lock; } ;
struct TYPE_2__ {scalar_t__ serdes_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mv88e6390_serdes_irq_disable (struct mv88e6xxx_chip*,int,int) ; 
 int mv88e6390x_serdes_get_lane (struct mv88e6xxx_chip*,int) ; 

void mv88e6390_serdes_irq_free(struct mv88e6xxx_chip *chip, int port)
{
	int lane = mv88e6390x_serdes_get_lane(chip, port);

	if (port < 9)
		return;

	if (lane < 0)
		return;

	mv88e6390_serdes_irq_disable(chip, port, lane);

	/* Freeing the IRQ will trigger irq callbacks. So we cannot
	 * hold the reg_lock.
	 */
	mutex_unlock(&chip->reg_lock);
	free_irq(chip->ports[port].serdes_irq, &chip->ports[port]);
	mutex_lock(&chip->reg_lock);

	chip->ports[port].serdes_irq = 0;
}