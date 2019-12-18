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
struct ps2dev {int dummy; } ;
struct psmouse {scalar_t__ model; struct ps2dev ps2dev; } ;

/* Variables and functions */
 scalar_t__ HGPK_MODEL_D ; 
 int PSMOUSE_CMD_DISABLE ; 
 int /*<<< orphan*/  PSMOUSE_IGNORE ; 
 int /*<<< orphan*/  PSMOUSE_INITIALIZING ; 
 int hgpk_reset_device (struct psmouse*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ ps2_command (struct ps2dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ps2_sendbyte (struct ps2dev*,int,int) ; 
 int /*<<< orphan*/  psmouse_activate (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*) ; 
 int /*<<< orphan*/  psmouse_err (struct psmouse*,char*) ; 
 int /*<<< orphan*/  psmouse_set_state (struct psmouse*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hgpk_toggle_powersave(struct psmouse *psmouse, int enable)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	int timeo;
	int err;

	/* Added on D-series touchpads */
	if (psmouse->model < HGPK_MODEL_D)
		return 0;

	if (enable) {
		psmouse_set_state(psmouse, PSMOUSE_INITIALIZING);

		/*
		 * Sending a byte will drive MS-DAT low; this will wake up
		 * the controller.  Once we get an ACK back from it, it
		 * means we can continue with the touchpad re-init.  ALPS
		 * tells us that 1s should be long enough, so set that as
		 * the upper bound. (in practice, it takes about 3 loops.)
		 */
		for (timeo = 20; timeo > 0; timeo--) {
			if (!ps2_sendbyte(ps2dev, PSMOUSE_CMD_DISABLE, 20))
				break;
			msleep(25);
		}

		err = hgpk_reset_device(psmouse, false);
		if (err) {
			psmouse_err(psmouse, "Failed to reset device!\n");
			return err;
		}

		/* should be all set, enable the touchpad */
		psmouse_activate(psmouse);
		psmouse_dbg(psmouse, "Touchpad powered up.\n");
	} else {
		psmouse_dbg(psmouse, "Powering off touchpad.\n");

		if (ps2_command(ps2dev, NULL, 0xec) ||
		    ps2_command(ps2dev, NULL, 0xec) ||
		    ps2_command(ps2dev, NULL, 0xea)) {
			return -1;
		}

		psmouse_set_state(psmouse, PSMOUSE_IGNORE);

		/* probably won't see an ACK, the touchpad will be off */
		ps2_sendbyte(ps2dev, 0xec, 20);
	}

	return 0;
}