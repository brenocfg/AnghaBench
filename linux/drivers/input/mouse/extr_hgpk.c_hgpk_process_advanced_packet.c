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
struct psmouse {unsigned char* packet; struct input_dev* dev; struct hgpk_data* private; } ;
struct input_dev {int dummy; } ;
struct hgpk_data {scalar_t__ mode; int abs_x; int abs_y; scalar_t__ dupe_count; int /*<<< orphan*/  recalib_wq; int /*<<< orphan*/  spew_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 scalar_t__ HGPK_MODE_GLIDESENSOR ; 
 scalar_t__ HGPK_MODE_PENTABLET ; 
 int /*<<< orphan*/  RECALIBRATING ; 
 scalar_t__ SPEW_WATCH_COUNT ; 
 scalar_t__ hgpk_discard_decay_hack (struct psmouse*,int,int) ; 
 int /*<<< orphan*/  hgpk_reset_hack_state (struct psmouse*) ; 
 int /*<<< orphan*/  hgpk_spewing_hack (struct psmouse*,int,int,int,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*,...) ; 
 int /*<<< orphan*/  psmouse_queue_work (struct psmouse*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spew_delay ; 
 scalar_t__ tpdebug ; 

__attribute__((used)) static void hgpk_process_advanced_packet(struct psmouse *psmouse)
{
	struct hgpk_data *priv = psmouse->private;
	struct input_dev *idev = psmouse->dev;
	unsigned char *packet = psmouse->packet;
	int down = !!(packet[2] & 2);
	int left = !!(packet[3] & 1);
	int right = !!(packet[3] & 2);
	int x = packet[1] | ((packet[2] & 0x78) << 4);
	int y = packet[4] | ((packet[3] & 0x70) << 3);

	if (priv->mode == HGPK_MODE_GLIDESENSOR) {
		int pt_down = !!(packet[2] & 1);
		int finger_down = !!(packet[2] & 2);
		int z = packet[5];

		input_report_abs(idev, ABS_PRESSURE, z);
		if (tpdebug)
			psmouse_dbg(psmouse, "pd=%d fd=%d z=%d",
				    pt_down, finger_down, z);
	} else {
		/*
		 * PenTablet mode does not report pressure, so we don't
		 * report it here
		 */
		if (tpdebug)
			psmouse_dbg(psmouse, "pd=%d ", down);
	}

	if (tpdebug)
		psmouse_dbg(psmouse, "l=%d r=%d x=%d y=%d\n",
			    left, right, x, y);

	input_report_key(idev, BTN_TOUCH, down);
	input_report_key(idev, BTN_LEFT, left);
	input_report_key(idev, BTN_RIGHT, right);

	/*
	 * If this packet says that the finger was removed, reset our position
	 * tracking so that we don't erroneously detect a jump on next press.
	 */
	if (!down) {
		hgpk_reset_hack_state(psmouse);
		goto done;
	}

	/*
	 * Weed out duplicate packets (we get quite a few, and they mess up
	 * our jump detection)
	 */
	if (x == priv->abs_x && y == priv->abs_y) {
		if (++priv->dupe_count > SPEW_WATCH_COUNT) {
			if (tpdebug)
				psmouse_dbg(psmouse, "hard spew detected\n");
			priv->spew_flag = RECALIBRATING;
			psmouse_queue_work(psmouse, &priv->recalib_wq,
					   msecs_to_jiffies(spew_delay));
		}
		goto done;
	}

	/* not a duplicate, continue with position reporting */
	priv->dupe_count = 0;

	/* Don't apply hacks in PT mode, it seems reliable */
	if (priv->mode != HGPK_MODE_PENTABLET && priv->abs_x != -1) {
		int x_diff = priv->abs_x - x;
		int y_diff = priv->abs_y - y;
		if (hgpk_discard_decay_hack(psmouse, x_diff, y_diff)) {
			if (tpdebug)
				psmouse_dbg(psmouse, "discarding\n");
			goto done;
		}
		hgpk_spewing_hack(psmouse, left, right, x_diff, y_diff);
	}

	input_report_abs(idev, ABS_X, x);
	input_report_abs(idev, ABS_Y, y);
	priv->abs_x = x;
	priv->abs_y = y;

done:
	input_sync(idev);
}