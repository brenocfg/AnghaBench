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
 int ENODEV ; 
 int /*<<< orphan*/  MAKE_PS2_CMD (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TP_COMMAND ; 
 int TP_POR ; 
 int ps2_command (struct ps2dev*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trackpoint_power_on_reset(struct ps2dev *ps2dev)
{
	u8 param[2] = { TP_POR };
	int err;

	err = ps2_command(ps2dev, param, MAKE_PS2_CMD(1, 2, TP_COMMAND));
	if (err)
		return err;

	/* Check for success response -- 0xAA00 */
	if (param[0] != 0xAA || param[1] != 0x00)
		return -ENODEV;

	return 0;
}