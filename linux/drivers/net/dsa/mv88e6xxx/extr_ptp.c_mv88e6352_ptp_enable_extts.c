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
struct TYPE_2__ {int flags; int /*<<< orphan*/  index; } ;
struct ptp_clock_request {TYPE_1__ extts; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  tai_event_work; int /*<<< orphan*/  ptp_clock; } ;

/* Variables and functions */
 int EBUSY ; 
 int MV88E6352_G2_SCRATCH_GPIO_PCTL_EVREQ ; 
 int MV88E6352_G2_SCRATCH_GPIO_PCTL_GPIO ; 
 int /*<<< orphan*/  PTP_CLOCK_EXTTS ; 
 int /*<<< orphan*/  PTP_PF_EXTTS ; 
 int PTP_RISING_EDGE ; 
 int /*<<< orphan*/  TAI_EVENT_WORK_INTERVAL ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int mv88e6352_config_eventcap (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 
 int mv88e6352_set_gpio_func (struct mv88e6xxx_chip*,int,int,int) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 
 int ptp_find_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e6352_ptp_enable_extts(struct mv88e6xxx_chip *chip,
				      struct ptp_clock_request *rq, int on)
{
	int rising = (rq->extts.flags & PTP_RISING_EDGE);
	int func;
	int pin;
	int err;

	pin = ptp_find_pin(chip->ptp_clock, PTP_PF_EXTTS, rq->extts.index);

	if (pin < 0)
		return -EBUSY;

	mv88e6xxx_reg_lock(chip);

	if (on) {
		func = MV88E6352_G2_SCRATCH_GPIO_PCTL_EVREQ;

		err = mv88e6352_set_gpio_func(chip, pin, func, true);
		if (err)
			goto out;

		schedule_delayed_work(&chip->tai_event_work,
				      TAI_EVENT_WORK_INTERVAL);

		err = mv88e6352_config_eventcap(chip, PTP_CLOCK_EXTTS, rising);
	} else {
		func = MV88E6352_G2_SCRATCH_GPIO_PCTL_GPIO;

		err = mv88e6352_set_gpio_func(chip, pin, func, true);

		cancel_delayed_work_sync(&chip->tai_event_work);
	}

out:
	mv88e6xxx_reg_unlock(chip);

	return err;
}