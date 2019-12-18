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
typedef  int u32 ;
typedef  int u16 ;
struct work_struct {int dummy; } ;
struct ptp_clock_event {int /*<<< orphan*/  timestamp; scalar_t__ index; int /*<<< orphan*/  type; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  tai_event_work; int /*<<< orphan*/  ptp_clock; int /*<<< orphan*/  tstamp_tc; int /*<<< orphan*/  dev; } ;
struct delayed_work {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  MV88E6XXX_TAI_EVENT_STATUS ; 
 int MV88E6XXX_TAI_EVENT_STATUS_ERROR ; 
 int MV88E6XXX_TAI_EVENT_STATUS_VALID ; 
 int /*<<< orphan*/  PTP_CLOCK_EXTTS ; 
 int /*<<< orphan*/  TAI_EVENT_WORK_INTERVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct mv88e6xxx_chip* dw_tai_event_to_chip (struct delayed_work*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_tai_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_tai_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptp_clock_event (int /*<<< orphan*/ ,struct ptp_clock_event*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timecounter_cyc2time (int /*<<< orphan*/ *,int) ; 
 struct delayed_work* to_delayed_work (struct work_struct*) ; 

__attribute__((used)) static void mv88e6352_tai_event_work(struct work_struct *ugly)
{
	struct delayed_work *dw = to_delayed_work(ugly);
	struct mv88e6xxx_chip *chip = dw_tai_event_to_chip(dw);
	struct ptp_clock_event ev;
	u16 status[4];
	u32 raw_ts;
	int err;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_tai_read(chip, MV88E6XXX_TAI_EVENT_STATUS,
				 status, ARRAY_SIZE(status));
	mv88e6xxx_reg_unlock(chip);

	if (err) {
		dev_err(chip->dev, "failed to read TAI status register\n");
		return;
	}
	if (status[0] & MV88E6XXX_TAI_EVENT_STATUS_ERROR) {
		dev_warn(chip->dev, "missed event capture\n");
		return;
	}
	if (!(status[0] & MV88E6XXX_TAI_EVENT_STATUS_VALID))
		goto out;

	raw_ts = ((u32)status[2] << 16) | status[1];

	/* Clear the valid bit so the next timestamp can come in */
	status[0] &= ~MV88E6XXX_TAI_EVENT_STATUS_VALID;
	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_tai_write(chip, MV88E6XXX_TAI_EVENT_STATUS, status[0]);
	mv88e6xxx_reg_unlock(chip);

	/* This is an external timestamp */
	ev.type = PTP_CLOCK_EXTTS;

	/* We only have one timestamping channel. */
	ev.index = 0;
	mv88e6xxx_reg_lock(chip);
	ev.timestamp = timecounter_cyc2time(&chip->tstamp_tc, raw_ts);
	mv88e6xxx_reg_unlock(chip);

	ptp_clock_event(chip->ptp_clock, &ev);
out:
	schedule_delayed_work(&chip->tai_event_work, TAI_EVENT_WORK_INTERVAL);
}