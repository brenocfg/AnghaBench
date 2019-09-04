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
struct psmouse {int /*<<< orphan*/  ps2dev; struct alps_data* private; } ;
struct alps_data {int flags; } ;

/* Variables and functions */
 int ALPS_PASS ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETSTREAM ; 
 scalar_t__ alps_absolute_mode_v1_v2 (struct psmouse*) ; 
 scalar_t__ alps_passthrough_mode_v2 (struct psmouse*,int) ; 
 scalar_t__ alps_tap_mode (struct psmouse*,int) ; 
 scalar_t__ ps2_command (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_err (struct psmouse*,char*) ; 
 int /*<<< orphan*/  psmouse_warn (struct psmouse*,char*) ; 

__attribute__((used)) static int alps_hw_init_v1_v2(struct psmouse *psmouse)
{
	struct alps_data *priv = psmouse->private;

	if ((priv->flags & ALPS_PASS) &&
	    alps_passthrough_mode_v2(psmouse, true)) {
		return -1;
	}

	if (alps_tap_mode(psmouse, true)) {
		psmouse_warn(psmouse, "Failed to enable hardware tapping\n");
		return -1;
	}

	if (alps_absolute_mode_v1_v2(psmouse)) {
		psmouse_err(psmouse, "Failed to enable absolute mode\n");
		return -1;
	}

	if ((priv->flags & ALPS_PASS) &&
	    alps_passthrough_mode_v2(psmouse, false)) {
		return -1;
	}

	/* ALPS needs stream mode, otherwise it won't report any data */
	if (ps2_command(&psmouse->ps2dev, NULL, PSMOUSE_CMD_SETSTREAM)) {
		psmouse_err(psmouse, "Failed to enable stream mode\n");
		return -1;
	}

	return 0;
}