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
struct psmouse {scalar_t__ model; struct hgpk_data* private; } ;
struct hgpk_data {scalar_t__ recalib_window; } ;

/* Variables and functions */
 scalar_t__ HGPK_MODEL_C ; 
 int /*<<< orphan*/  PSMOUSE_INITIALIZING ; 
 int /*<<< orphan*/  autorecal ; 
 int hgpk_reset_device (struct psmouse*,int) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 
 scalar_t__ psmouse_activate (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*) ; 
 int /*<<< orphan*/  psmouse_set_state (struct psmouse*,int /*<<< orphan*/ ) ; 
 scalar_t__ recal_guard_time ; 
 scalar_t__ tpdebug ; 

__attribute__((used)) static int hgpk_force_recalibrate(struct psmouse *psmouse)
{
	struct hgpk_data *priv = psmouse->private;
	int err;

	/* C-series touchpads added the recalibrate command */
	if (psmouse->model < HGPK_MODEL_C)
		return 0;

	if (!autorecal) {
		psmouse_dbg(psmouse, "recalibration disabled, ignoring\n");
		return 0;
	}

	psmouse_dbg(psmouse, "recalibrating touchpad..\n");

	/* we don't want to race with the irq handler, nor with resyncs */
	psmouse_set_state(psmouse, PSMOUSE_INITIALIZING);

	/* start by resetting the device */
	err = hgpk_reset_device(psmouse, true);
	if (err)
		return err;

	/*
	 * XXX: If a finger is down during this delay, recalibration will
	 * detect capacitance incorrectly.  This is a hardware bug, and
	 * we don't have a good way to deal with it.  The 2s window stuff
	 * (below) is our best option for now.
	 */
	if (psmouse_activate(psmouse))
		return -1;

	if (tpdebug)
		psmouse_dbg(psmouse, "touchpad reactivated\n");

	/*
	 * If we get packets right away after recalibrating, it's likely
	 * that a finger was on the touchpad.  If so, it's probably
	 * miscalibrated, so we optionally schedule another.
	 */
	if (recal_guard_time)
		priv->recalib_window = jiffies +
			msecs_to_jiffies(recal_guard_time);

	return 0;
}