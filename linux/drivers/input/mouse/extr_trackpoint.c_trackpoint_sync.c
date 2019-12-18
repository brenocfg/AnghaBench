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
struct trackpoint_data {scalar_t__ variant_id; } ;
struct psmouse {int /*<<< orphan*/  ps2dev; struct trackpoint_data* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  TP_DEF_MB ; 
 int /*<<< orphan*/  TP_DEF_SOURCE_TAG ; 
 int /*<<< orphan*/  TP_DEF_TWOHAND ; 
 int /*<<< orphan*/  TP_MASK_MB ; 
 int /*<<< orphan*/  TP_MASK_SOURCE_TAG ; 
 int /*<<< orphan*/  TP_MASK_TWOHAND ; 
 int /*<<< orphan*/  TP_TOGGLE_MB ; 
 int /*<<< orphan*/  TP_TOGGLE_SOURCE_TAG ; 
 int /*<<< orphan*/  TP_TOGGLE_TWOHAND ; 
 scalar_t__ TP_VARIANT_IBM ; 
 int /*<<< orphan*/  TRACKPOINT_UPDATE (int,struct psmouse*,struct trackpoint_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draghys ; 
 int /*<<< orphan*/  drift_time ; 
 int /*<<< orphan*/  ext_dev ; 
 int /*<<< orphan*/  inertia ; 
 int /*<<< orphan*/  jenks ; 
 int /*<<< orphan*/  mindrag ; 
 int /*<<< orphan*/  press_to_select ; 
 int /*<<< orphan*/  reach ; 
 int /*<<< orphan*/  sensitivity ; 
 int /*<<< orphan*/  skipback ; 
 int /*<<< orphan*/  speed ; 
 int /*<<< orphan*/  thresh ; 
 int /*<<< orphan*/  trackpoint_update_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upthresh ; 
 int /*<<< orphan*/  ztime ; 

__attribute__((used)) static int trackpoint_sync(struct psmouse *psmouse, bool in_power_on_state)
{
	struct trackpoint_data *tp = psmouse->private;

	if (!in_power_on_state && tp->variant_id == TP_VARIANT_IBM) {
		/*
		 * Disable features that may make device unusable
		 * with this driver.
		 */
		trackpoint_update_bit(&psmouse->ps2dev, TP_TOGGLE_TWOHAND,
				      TP_MASK_TWOHAND, TP_DEF_TWOHAND);

		trackpoint_update_bit(&psmouse->ps2dev, TP_TOGGLE_SOURCE_TAG,
				      TP_MASK_SOURCE_TAG, TP_DEF_SOURCE_TAG);

		trackpoint_update_bit(&psmouse->ps2dev, TP_TOGGLE_MB,
				      TP_MASK_MB, TP_DEF_MB);
	}

	/*
	 * These properties can be changed in this driver. Only
	 * configure them if the values are non-default or if the TP is in
	 * an unknown state.
	 */
	TRACKPOINT_UPDATE(in_power_on_state, psmouse, tp, sensitivity);
	TRACKPOINT_UPDATE(in_power_on_state, psmouse, tp, inertia);
	TRACKPOINT_UPDATE(in_power_on_state, psmouse, tp, speed);
	TRACKPOINT_UPDATE(in_power_on_state, psmouse, tp, reach);
	TRACKPOINT_UPDATE(in_power_on_state, psmouse, tp, draghys);
	TRACKPOINT_UPDATE(in_power_on_state, psmouse, tp, mindrag);
	TRACKPOINT_UPDATE(in_power_on_state, psmouse, tp, thresh);
	TRACKPOINT_UPDATE(in_power_on_state, psmouse, tp, upthresh);
	TRACKPOINT_UPDATE(in_power_on_state, psmouse, tp, ztime);
	TRACKPOINT_UPDATE(in_power_on_state, psmouse, tp, jenks);
	TRACKPOINT_UPDATE(in_power_on_state, psmouse, tp, drift_time);

	/* toggles */
	TRACKPOINT_UPDATE(in_power_on_state, psmouse, tp, press_to_select);
	TRACKPOINT_UPDATE(in_power_on_state, psmouse, tp, skipback);
	TRACKPOINT_UPDATE(in_power_on_state, psmouse, tp, ext_dev);

	return 0;
}