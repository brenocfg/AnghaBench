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
struct ptp_clock_info {int dummy; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  tstamp_tc; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 
 struct mv88e6xxx_chip* ptp_to_chip (struct ptp_clock_info*) ; 
 int /*<<< orphan*/  timecounter_adjtime (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e6xxx_ptp_adjtime(struct ptp_clock_info *ptp, s64 delta)
{
	struct mv88e6xxx_chip *chip = ptp_to_chip(ptp);

	mv88e6xxx_reg_lock(chip);
	timecounter_adjtime(&chip->tstamp_tc, delta);
	mv88e6xxx_reg_unlock(chip);

	return 0;
}