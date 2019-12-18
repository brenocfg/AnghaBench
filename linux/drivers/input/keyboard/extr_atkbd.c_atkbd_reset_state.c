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
struct ps2dev {int dummy; } ;
struct atkbd {struct ps2dev ps2dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATKBD_CMD_SETLEDS ; 
 int /*<<< orphan*/  ATKBD_CMD_SETREP ; 
 scalar_t__ ps2_command (struct ps2dev*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atkbd_reset_state(struct atkbd *atkbd)
{
        struct ps2dev *ps2dev = &atkbd->ps2dev;
	unsigned char param[1];

/*
 * Set the LEDs to a predefined state (all off).
 */

	param[0] = 0;
	if (ps2_command(ps2dev, param, ATKBD_CMD_SETLEDS))
		return -1;

/*
 * Set autorepeat to fastest possible.
 */

	param[0] = 0;
	if (ps2_command(ps2dev, param, ATKBD_CMD_SETREP))
		return -1;

	return 0;
}