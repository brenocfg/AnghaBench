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
struct cx8802_driver {struct cx88_core* core; } ;

/* Variables and functions */
#define  CX88_BOARD_HAUPPAUGE_HVR1300 128 
 int ENODEV ; 
 int /*<<< orphan*/  MO_GP0_IO ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int cx8802_blackbird_advise_acquire(struct cx8802_driver *drv)
{
	struct cx88_core *core = drv->core;
	int err = 0;

	switch (core->boardnr) {
	case CX88_BOARD_HAUPPAUGE_HVR1300:
		/*
		 * By default, core setup will leave the cx22702 out of reset,
		 * on the bus.
		 * We left the hardware on power up with the cx22702 active.
		 * We're being given access to re-arrange the GPIOs.
		 * Take the bus off the cx22702 and put the cx23416 on it.
		 */
		/* Toggle reset on cx22702 leaving i2c active */
		cx_set(MO_GP0_IO, 0x00000080);
		udelay(1000);
		cx_clear(MO_GP0_IO, 0x00000080);
		udelay(50);
		cx_set(MO_GP0_IO, 0x00000080);
		udelay(1000);
		/* tri-state the cx22702 pins */
		cx_set(MO_GP0_IO, 0x00000004);
		udelay(1000);
		break;
	default:
		err = -ENODEV;
	}
	return err;
}