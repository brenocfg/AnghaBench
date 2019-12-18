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
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6390_G1_MONITOR_MGMT_CTL_PTR_CPU_DEST ; 
 int mv88e6390_g1_monitor_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 

int mv88e6390_g1_set_cpu_port(struct mv88e6xxx_chip *chip, int port)
{
	u16 ptr = MV88E6390_G1_MONITOR_MGMT_CTL_PTR_CPU_DEST;

	return mv88e6390_g1_monitor_write(chip, ptr, port);
}