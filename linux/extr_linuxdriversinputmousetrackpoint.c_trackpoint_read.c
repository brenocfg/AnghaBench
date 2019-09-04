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
typedef  int /*<<< orphan*/  u8 ;
struct ps2dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAKE_PS2_CMD (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TP_COMMAND ; 
 int ps2_command (struct ps2dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trackpoint_read(struct ps2dev *ps2dev, u8 loc, u8 *results)
{
	results[0] = loc;

	return ps2_command(ps2dev, results, MAKE_PS2_CMD(1, 1, TP_COMMAND));
}