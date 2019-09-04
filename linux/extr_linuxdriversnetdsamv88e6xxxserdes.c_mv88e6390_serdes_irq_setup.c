#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  domain; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  reg_lock; TYPE_2__* ports; TYPE_1__ g2_irq; } ;
struct TYPE_4__ {scalar_t__ serdes_irq; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int mv88e6390_serdes_irq_enable (struct mv88e6xxx_chip*,int,int) ; 
 int /*<<< orphan*/  mv88e6390_serdes_thread_fn ; 
 int mv88e6390x_serdes_get_lane (struct mv88e6xxx_chip*,int) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 

int mv88e6390_serdes_irq_setup(struct mv88e6xxx_chip *chip, int port)
{
	int lane;
	int err;

	/* Only support ports 9 and 10 at the moment */
	if (port < 9)
		return 0;

	lane = mv88e6390x_serdes_get_lane(chip, port);

	if (lane == -ENODEV)
		return 0;

	if (lane < 0)
		return lane;

	chip->ports[port].serdes_irq = irq_find_mapping(chip->g2_irq.domain,
							port);
	if (chip->ports[port].serdes_irq < 0) {
		dev_err(chip->dev, "Unable to map SERDES irq: %d\n",
			chip->ports[port].serdes_irq);
		return chip->ports[port].serdes_irq;
	}

	/* Requesting the IRQ will trigger irq callbacks. So we cannot
	 * hold the reg_lock.
	 */
	mutex_unlock(&chip->reg_lock);
	err = request_threaded_irq(chip->ports[port].serdes_irq, NULL,
				   mv88e6390_serdes_thread_fn,
				   IRQF_ONESHOT, "mv88e6xxx-serdes",
				   &chip->ports[port]);
	mutex_lock(&chip->reg_lock);

	if (err) {
		dev_err(chip->dev, "Unable to request SERDES interrupt: %d\n",
			err);
		return err;
	}

	return mv88e6390_serdes_irq_enable(chip, port, lane);
}