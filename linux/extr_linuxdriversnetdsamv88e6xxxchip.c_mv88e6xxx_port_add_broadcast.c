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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC ; 
 int mv88e6xxx_port_db_load_purge (struct mv88e6xxx_chip*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e6xxx_port_add_broadcast(struct mv88e6xxx_chip *chip, int port,
					u16 vid)
{
	const char broadcast[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
	u8 state = MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC;

	return mv88e6xxx_port_db_load_purge(chip, port, broadcast, vid, state);
}