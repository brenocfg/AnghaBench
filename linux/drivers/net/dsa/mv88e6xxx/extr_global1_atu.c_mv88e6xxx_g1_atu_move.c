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
struct mv88e6xxx_atu_entry {int state; int portvec; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {unsigned long atu_move_port_mask; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int bitmap_weight (unsigned long*,int) ; 
 int mv88e6xxx_g1_atu_flushmove (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,struct mv88e6xxx_atu_entry*,int) ; 

__attribute__((used)) static int mv88e6xxx_g1_atu_move(struct mv88e6xxx_chip *chip, u16 fid,
				 int from_port, int to_port, bool all)
{
	struct mv88e6xxx_atu_entry entry = { 0 };
	unsigned long mask;
	int shift;

	if (!chip->info->atu_move_port_mask)
		return -EOPNOTSUPP;

	mask = chip->info->atu_move_port_mask;
	shift = bitmap_weight(&mask, 16);

	entry.state = 0xf, /* Full EntryState means Move */
	entry.portvec = from_port & mask;
	entry.portvec |= (to_port & mask) << shift;

	return mv88e6xxx_g1_atu_flushmove(chip, fid, &entry, all);
}