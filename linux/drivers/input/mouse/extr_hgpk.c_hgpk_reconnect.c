#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* serio; } ;
struct psmouse {TYPE_5__ ps2dev; struct hgpk_data* private; } ;
struct hgpk_data {int powered; } ;
struct TYPE_6__ {scalar_t__ event; } ;
struct TYPE_7__ {TYPE_1__ power_state; } ;
struct TYPE_8__ {TYPE_2__ power; } ;
struct TYPE_9__ {TYPE_3__ dev; } ;

/* Variables and functions */
 scalar_t__ PM_EVENT_ON ; 
 int hgpk_reset_device (struct psmouse*,int) ; 
 int /*<<< orphan*/  olpc_board (int) ; 
 scalar_t__ olpc_board_at_least (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hgpk_reconnect(struct psmouse *psmouse)
{
	struct hgpk_data *priv = psmouse->private;

	/*
	 * During suspend/resume the ps2 rails remain powered.  We don't want
	 * to do a reset because it's flush data out of buffers; however,
	 * earlier prototypes (B1) had some brokenness that required a reset.
	 */
	if (olpc_board_at_least(olpc_board(0xb2)))
		if (psmouse->ps2dev.serio->dev.power.power_state.event !=
				PM_EVENT_ON)
			return 0;

	priv->powered = 1;
	return hgpk_reset_device(psmouse, false);
}