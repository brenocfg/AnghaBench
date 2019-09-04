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
struct psmouse {struct ps2dev ps2dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hgpk_reset_hack_state (struct psmouse*) ; 
 int hgpk_select_mode (struct psmouse*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ ps2_command (struct ps2dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  psmouse_err (struct psmouse*,char*) ; 
 int /*<<< orphan*/  psmouse_reset (struct psmouse*) ; 

__attribute__((used)) static int hgpk_reset_device(struct psmouse *psmouse, bool recalibrate)
{
	int err;

	psmouse_reset(psmouse);

	if (recalibrate) {
		struct ps2dev *ps2dev = &psmouse->ps2dev;

		/* send the recalibrate request */
		if (ps2_command(ps2dev, NULL, 0xf5) ||
		    ps2_command(ps2dev, NULL, 0xf5) ||
		    ps2_command(ps2dev, NULL, 0xe6) ||
		    ps2_command(ps2dev, NULL, 0xf5)) {
			return -1;
		}

		/* according to ALPS, 150mS is required for recalibration */
		msleep(150);
	}

	err = hgpk_select_mode(psmouse);
	if (err) {
		psmouse_err(psmouse, "failed to select mode\n");
		return err;
	}

	hgpk_reset_hack_state(psmouse);

	return 0;
}