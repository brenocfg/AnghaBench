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
struct mv88e6xxx_atu_entry {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int mv88e6xxx_g1_atu_flushmove (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,struct mv88e6xxx_atu_entry*,int) ; 

int mv88e6xxx_g1_atu_flush(struct mv88e6xxx_chip *chip, u16 fid, bool all)
{
	struct mv88e6xxx_atu_entry entry = {
		.state = 0, /* Null EntryState means Flush */
	};

	return mv88e6xxx_g1_atu_flushmove(chip, fid, &entry, all);
}