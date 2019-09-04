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
typedef  int /*<<< orphan*/  uint64_t ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_G1_STATS_OP_BANK_1_BIT_9 ; 
 int /*<<< orphan*/  MV88E6XXX_G1_STATS_OP_HIST_RX_TX ; 
 int STATS_TYPE_BANK0 ; 
 int STATS_TYPE_BANK1 ; 
 int mv88e6xxx_stats_get_stats (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e6320_stats_get_stats(struct mv88e6xxx_chip *chip, int port,
				     uint64_t *data)
{
	return mv88e6xxx_stats_get_stats(chip, port, data,
					 STATS_TYPE_BANK0 | STATS_TYPE_BANK1,
					 MV88E6XXX_G1_STATS_OP_BANK_1_BIT_9,
					 MV88E6XXX_G1_STATS_OP_HIST_RX_TX);
}