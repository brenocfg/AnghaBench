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
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6352_G2_IRL_CMD_OP_INIT_ALL ; 
 int mv88e6xxx_g2_irl_op (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mv88e6352_g2_irl_init_all(struct mv88e6xxx_chip *chip, int port)
{
	return mv88e6xxx_g2_irl_op(chip, MV88E6352_G2_IRL_CMD_OP_INIT_ALL, port,
				   0, 0);
}