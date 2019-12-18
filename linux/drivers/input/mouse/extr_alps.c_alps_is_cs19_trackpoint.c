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
typedef  int u8 ;
struct psmouse {int /*<<< orphan*/  ps2dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAKE_PS2_CMD (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TP_READ_ID ; 
 int TP_VARIANT_ALPS ; 
 scalar_t__ ps2_command (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool alps_is_cs19_trackpoint(struct psmouse *psmouse)
{
	u8 param[2] = { 0 };

	if (ps2_command(&psmouse->ps2dev,
			param, MAKE_PS2_CMD(0, 2, TP_READ_ID)))
		return false;

	/*
	 * param[0] contains the trackpoint device variant_id while
	 * param[1] contains the firmware_id. So far all alps
	 * trackpoint-only devices have their variant_ids equal
	 * TP_VARIANT_ALPS and their firmware_ids are in 0x20~0x2f range.
	 */
	return param[0] == TP_VARIANT_ALPS && ((param[1] & 0xf0) == 0x20);
}