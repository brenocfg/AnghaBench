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
struct trackpoint_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACKPOINT_SET_POWER_ON_DEFAULT (struct trackpoint_data*,int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  upthresh ; 
 int /*<<< orphan*/  ztime ; 

__attribute__((used)) static void trackpoint_defaults(struct trackpoint_data *tp)
{
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, sensitivity);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, speed);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, reach);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, draghys);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, mindrag);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, thresh);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, upthresh);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, ztime);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, jenks);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, drift_time);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, inertia);

	/* toggles */
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, press_to_select);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, skipback);
	TRACKPOINT_SET_POWER_ON_DEFAULT(tp, ext_dev);
}