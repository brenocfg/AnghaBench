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
 int /*<<< orphan*/  MV88E6390_G2_AVB_CMD_PORT_PTPGLOBAL ; 
 int mv88e6390_g2_avb_port_ptp_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e6390_g2_avb_ptp_write(struct mv88e6xxx_chip *chip, int addr,
				      u16 data)
{
	return mv88e6390_g2_avb_port_ptp_write(chip,
					MV88E6390_G2_AVB_CMD_PORT_PTPGLOBAL,
					addr, data);
}