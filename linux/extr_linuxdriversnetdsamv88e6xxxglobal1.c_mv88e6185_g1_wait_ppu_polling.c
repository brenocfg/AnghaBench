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
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MV88E6185_G1_STS_PPU_STATE_MASK ; 
 int /*<<< orphan*/  MV88E6185_G1_STS_PPU_STATE_POLLING ; 
 int /*<<< orphan*/  MV88E6XXX_G1_STS ; 
 int mv88e6xxx_g1_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mv88e6185_g1_wait_ppu_polling(struct mv88e6xxx_chip *chip)
{
	u16 state;
	int i, err;

	for (i = 0; i < 16; ++i) {
		err = mv88e6xxx_g1_read(chip, MV88E6XXX_G1_STS, &state);
		if (err)
			return err;

		/* Check the value of the PPUState bits 15:14 */
		state &= MV88E6185_G1_STS_PPU_STATE_MASK;
		if (state == MV88E6185_G1_STS_PPU_STATE_POLLING)
			return 0;

		usleep_range(1000, 2000);
	}

	return -ETIMEDOUT;
}