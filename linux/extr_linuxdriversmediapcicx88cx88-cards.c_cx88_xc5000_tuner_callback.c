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
struct cx88_core {int boardnr; } ;

/* Variables and functions */
#define  CX88_BOARD_DVICO_FUSIONHDTV_7_GOLD 129 
#define  CX88_BOARD_PINNACLE_PCTV_HD_800i 128 
 int EINVAL ; 
 int /*<<< orphan*/  MO_GP0_IO ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int cx88_xc5000_tuner_callback(struct cx88_core *core,
				      int command, int arg)
{
	switch (core->boardnr) {
	case CX88_BOARD_PINNACLE_PCTV_HD_800i:
		if (command == 0) { /* This is the reset command from xc5000 */

			/*
			 * djh - According to the engineer at PCTV Systems,
			 * the xc5000 reset pin is supposed to be on GPIO12.
			 * However, despite three nights of effort, pulling
			 * that GPIO low didn't reset the xc5000.  While
			 * pulling MO_SRST_IO low does reset the xc5000, this
			 * also resets in the s5h1409 being reset as well.
			 * This causes tuning to always fail since the internal
			 * state of the s5h1409 does not match the driver's
			 * state.  Given that the only two conditions in which
			 * the driver performs a reset is during firmware load
			 * and powering down the chip, I am taking out the
			 * reset.  We know that the chip is being reset
			 * when the cx88 comes online, and not being able to
			 * do power management for this board is worse than
			 * not having any tuning at all.
			 */
			return 0;
		}

		dprintk(1, "xc5000: unknown tuner callback command.\n");
		return -EINVAL;
	case CX88_BOARD_DVICO_FUSIONHDTV_7_GOLD:
		if (command == 0) { /* This is the reset command from xc5000 */
			cx_clear(MO_GP0_IO, 0x00000010);
			usleep_range(10000, 20000);
			cx_set(MO_GP0_IO, 0x00000010);
			return 0;
		}

		dprintk(1, "xc5000: unknown tuner callback command.\n");
		return -EINVAL;
	}
	return 0; /* Should never be here */
}