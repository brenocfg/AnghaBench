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
 scalar_t__ TP_VARIANT_IBM ; 
 scalar_t__ trackpoint_power_on_reset (int /*<<< orphan*/ *) ; 
 int trackpoint_start_protocol (struct psmouse*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int trackpoint_sync (struct psmouse*,int) ; 

__attribute__((used)) static int trackpoint_reconnect(struct psmouse *psmouse)
{
	struct trackpoint_data *tp = psmouse->private;
	int error;
	bool was_reset;

	error = trackpoint_start_protocol(psmouse, NULL, NULL);
	if (error)
		return error;

	was_reset = tp->variant_id == TP_VARIANT_IBM &&
		    trackpoint_power_on_reset(&psmouse->ps2dev) == 0;

	error = trackpoint_sync(psmouse, was_reset);
	if (error)
		return error;

	return 0;
}