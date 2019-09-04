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
struct work_struct {int dummy; } ;
struct timespec64 {int dummy; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  overflow_work; int /*<<< orphan*/  ptp_clock_info; } ;
struct delayed_work {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_TAI_OVERFLOW_PERIOD ; 
 struct mv88e6xxx_chip* dw_overflow_to_chip (struct delayed_work*) ; 
 int /*<<< orphan*/  mv88e6xxx_ptp_gettime (int /*<<< orphan*/ *,struct timespec64*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct delayed_work* to_delayed_work (struct work_struct*) ; 

__attribute__((used)) static void mv88e6xxx_ptp_overflow_check(struct work_struct *work)
{
	struct delayed_work *dw = to_delayed_work(work);
	struct mv88e6xxx_chip *chip = dw_overflow_to_chip(dw);
	struct timespec64 ts;

	mv88e6xxx_ptp_gettime(&chip->ptp_clock_info, &ts);

	schedule_delayed_work(&chip->overflow_work,
			      MV88E6XXX_TAI_OVERFLOW_PERIOD);
}