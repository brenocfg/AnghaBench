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
typedef  int u16 ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6165_PTP_CFG ; 
 int MV88E6165_PTP_CFG_DISABLE_PTP ; 
 int MV88E6165_PTP_CFG_TSPEC_MASK ; 
 int mv88e6xxx_ptp_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int*) ; 
 int mv88e6xxx_ptp_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 

int mv88e6165_global_enable(struct mv88e6xxx_chip *chip)
{
	u16 val;
	int err;

	err = mv88e6xxx_ptp_read(chip, MV88E6165_PTP_CFG, &val);
	if (err)
		return err;

	val &= ~(MV88E6165_PTP_CFG_DISABLE_PTP | MV88E6165_PTP_CFG_TSPEC_MASK);

	return mv88e6xxx_ptp_write(chip, MV88E6165_PTP_CFG, val);
}