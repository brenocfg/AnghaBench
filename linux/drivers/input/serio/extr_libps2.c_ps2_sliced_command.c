#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ps2dev {TYPE_1__* serio; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS2_CMD_SETRES ; 
 int /*<<< orphan*/  PS2_CMD_SETSCALE11 ; 
 int __ps2_command (struct ps2dev*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  ps2_begin_command (struct ps2dev*) ; 
 int /*<<< orphan*/  ps2_end_command (struct ps2dev*) ; 

int ps2_sliced_command(struct ps2dev *ps2dev, u8 command)
{
	int i;
	int retval;

	ps2_begin_command(ps2dev);

	retval = __ps2_command(ps2dev, NULL, PS2_CMD_SETSCALE11);
	if (retval)
		goto out;

	for (i = 6; i >= 0; i -= 2) {
		u8 d = (command >> i) & 3;
		retval = __ps2_command(ps2dev, &d, PS2_CMD_SETRES);
		if (retval)
			break;
	}

out:
	dev_dbg(&ps2dev->serio->dev, "%02x - %d\n", command, retval);
	ps2_end_command(ps2dev);
	return retval;
}