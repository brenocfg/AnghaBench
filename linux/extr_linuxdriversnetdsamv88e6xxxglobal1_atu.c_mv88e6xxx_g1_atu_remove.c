#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_chip {TYPE_1__* info; } ;
struct TYPE_2__ {int atu_move_port_mask; } ;

/* Variables and functions */
 int mv88e6xxx_g1_atu_move (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int,int,int) ; 

int mv88e6xxx_g1_atu_remove(struct mv88e6xxx_chip *chip, u16 fid, int port,
			    bool all)
{
	int from_port = port;
	int to_port = chip->info->atu_move_port_mask;

	return mv88e6xxx_g1_atu_move(chip, fid, from_port, to_port, all);
}