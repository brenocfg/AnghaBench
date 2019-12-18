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
struct ps2dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAKE_PS2_CMD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TP_COMMAND ; 
 int TP_TOGGLE ; 
 int ps2_command (struct ps2dev*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trackpoint_toggle_bit(struct ps2dev *ps2dev, u8 loc, u8 mask)
{
	u8 param[3] = { TP_TOGGLE, loc, mask };

	/* Bad things will happen if the loc param isn't in this range */
	if (loc < 0x20 || loc >= 0x2F)
		return -EINVAL;

	return ps2_command(ps2dev, param, MAKE_PS2_CMD(3, 0, TP_COMMAND));
}