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
 int /*<<< orphan*/  MV88E6XXX_G2_PVT_ADDR ; 
 int MV88E6XXX_G2_PVT_ADDR_BUSY ; 
 int mv88e6xxx_g2_pvt_op_wait (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_g2_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv88e6xxx_g2_pvt_op(struct mv88e6xxx_chip *chip, int src_dev,
			       int src_port, u16 op)
{
	int err;

	/* 9-bit Cross-chip PVT pointer: with MV88E6XXX_G2_MISC_5_BIT_PORT
	 * cleared, source device is 5-bit, source port is 4-bit.
	 */
	op |= MV88E6XXX_G2_PVT_ADDR_BUSY;
	op |= (src_dev & 0x1f) << 4;
	op |= (src_port & 0xf);

	err = mv88e6xxx_g2_write(chip, MV88E6XXX_G2_PVT_ADDR, op);
	if (err)
		return err;

	return mv88e6xxx_g2_pvt_op_wait(chip);
}