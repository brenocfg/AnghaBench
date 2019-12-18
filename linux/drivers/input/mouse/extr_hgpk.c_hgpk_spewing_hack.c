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
struct psmouse {struct hgpk_data* private; } ;
struct hgpk_data {int x_tally; int y_tally; int spew_flag; int /*<<< orphan*/  recalib_wq; int /*<<< orphan*/  spew_count; } ;

/* Variables and functions */
#define  MAYBE_SPEWING 131 
#define  NO_SPEW 130 
#define  RECALIBRATING 129 
#define  SPEW_DETECTED 128 
 int /*<<< orphan*/  SPEW_WATCH_COUNT ; 
 int abs (int) ; 
 int /*<<< orphan*/  hgpk_reset_spew_detection (struct hgpk_data*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_queue_work (struct psmouse*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_warn (struct psmouse*,char*,int,int) ; 
 int /*<<< orphan*/  spew_delay ; 

__attribute__((used)) static void hgpk_spewing_hack(struct psmouse *psmouse,
			      int l, int r, int x, int y)
{
	struct hgpk_data *priv = psmouse->private;

	/* ignore button press packets; many in a row could trigger
	 * a false-positive! */
	if (l || r)
		return;

	/* don't track spew if the workaround feature has been turned off */
	if (!spew_delay)
		return;

	if (abs(x) > 3 || abs(y) > 3) {
		/* no spew, or spew ended */
		hgpk_reset_spew_detection(priv);
		return;
	}

	/* Keep a tally of the overall delta to the cursor position caused by
	 * the spew */
	priv->x_tally += x;
	priv->y_tally += y;

	switch (priv->spew_flag) {
	case NO_SPEW:
		/* we're not spewing, but this packet might be the start */
		priv->spew_flag = MAYBE_SPEWING;

		/* fall-through */

	case MAYBE_SPEWING:
		priv->spew_count++;

		if (priv->spew_count < SPEW_WATCH_COUNT)
			break;

		/* excessive spew detected, request recalibration */
		priv->spew_flag = SPEW_DETECTED;

		/* fall-through */

	case SPEW_DETECTED:
		/* only recalibrate when the overall delta to the cursor
		 * is really small. if the spew is causing significant cursor
		 * movement, it is probably a case of the user moving the
		 * cursor very slowly across the screen. */
		if (abs(priv->x_tally) < 3 && abs(priv->y_tally) < 3) {
			psmouse_warn(psmouse, "packet spew detected (%d,%d)\n",
				     priv->x_tally, priv->y_tally);
			priv->spew_flag = RECALIBRATING;
			psmouse_queue_work(psmouse, &priv->recalib_wq,
					   msecs_to_jiffies(spew_delay));
		}

		break;
	case RECALIBRATING:
		/* we already detected a spew and requested a recalibration,
		 * just wait for the queue to kick into action. */
		break;
	}
}