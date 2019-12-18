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
 int /*<<< orphan*/  MV88E6185_G1_STS_PPU_STATE_DISABLED ; 
 int /*<<< orphan*/  MV88E6185_G1_STS_PPU_STATE_MASK ; 
 int /*<<< orphan*/  MV88E6XXX_G1_STS ; 
 int mv88e6xxx_g1_wait_mask (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e6185_g1_wait_ppu_disabled(struct mv88e6xxx_chip *chip)
{
	return mv88e6xxx_g1_wait_mask(chip, MV88E6XXX_G1_STS,
				      MV88E6185_G1_STS_PPU_STATE_MASK,
				      MV88E6185_G1_STS_PPU_STATE_DISABLED);
}