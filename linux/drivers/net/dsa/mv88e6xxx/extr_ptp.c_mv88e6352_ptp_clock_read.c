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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct mv88e6xxx_chip {int dummy; } ;
struct cyclecounter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  MV88E6XXX_TAI_TIME_LO ; 
 struct mv88e6xxx_chip* cc_to_chip (struct cyclecounter const*) ; 
 int mv88e6xxx_tai_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 mv88e6352_ptp_clock_read(const struct cyclecounter *cc)
{
	struct mv88e6xxx_chip *chip = cc_to_chip(cc);
	u16 phc_time[2];
	int err;

	err = mv88e6xxx_tai_read(chip, MV88E6XXX_TAI_TIME_LO, phc_time,
				 ARRAY_SIZE(phc_time));
	if (err)
		return 0;
	else
		return ((u32)phc_time[1] << 16) | phc_time[0];
}