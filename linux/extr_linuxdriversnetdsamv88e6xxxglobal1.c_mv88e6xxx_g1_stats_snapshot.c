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
 int /*<<< orphan*/  MV88E6XXX_G1_STATS_OP ; 
 int MV88E6XXX_G1_STATS_OP_BUSY ; 
 int MV88E6XXX_G1_STATS_OP_CAPTURE_PORT ; 
 int MV88E6XXX_G1_STATS_OP_HIST_RX_TX ; 
 int mv88e6xxx_g1_stats_wait (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_g1_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 

int mv88e6xxx_g1_stats_snapshot(struct mv88e6xxx_chip *chip, int port)
{
	int err;

	/* Snapshot the hardware statistics counters for this port. */
	err = mv88e6xxx_g1_write(chip, MV88E6XXX_G1_STATS_OP,
				 MV88E6XXX_G1_STATS_OP_BUSY |
				 MV88E6XXX_G1_STATS_OP_CAPTURE_PORT |
				 MV88E6XXX_G1_STATS_OP_HIST_RX_TX | port);
	if (err)
		return err;

	/* Wait for the snapshotting to complete. */
	return mv88e6xxx_g1_stats_wait(chip);
}