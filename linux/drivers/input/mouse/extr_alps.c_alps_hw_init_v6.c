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
struct psmouse {int dummy; } ;

/* Variables and functions */
 scalar_t__ alps_absolute_mode_v6 (struct psmouse*) ; 
 scalar_t__ alps_passthrough_mode_v2 (struct psmouse*,int) ; 
 int alps_trackstick_enter_extended_mode_v3_v6 (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_err (struct psmouse*,char*) ; 

__attribute__((used)) static int alps_hw_init_v6(struct psmouse *psmouse)
{
	int ret;

	/* Enter passthrough mode to let trackpoint enter 6byte raw mode */
	if (alps_passthrough_mode_v2(psmouse, true))
		return -1;

	ret = alps_trackstick_enter_extended_mode_v3_v6(psmouse);

	if (alps_passthrough_mode_v2(psmouse, false))
		return -1;

	if (ret)
		return ret;

	if (alps_absolute_mode_v6(psmouse)) {
		psmouse_err(psmouse, "Failed to enable absolute mode\n");
		return -1;
	}

	return 0;
}