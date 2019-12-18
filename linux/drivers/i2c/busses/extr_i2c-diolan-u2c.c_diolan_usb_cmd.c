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
struct i2c_diolan_u2c {int /*<<< orphan*/  ocount; int /*<<< orphan*/  olen; int /*<<< orphan*/ * obuffer; } ;

/* Variables and functions */
 int diolan_write_cmd (struct i2c_diolan_u2c*,int) ; 

__attribute__((used)) static int diolan_usb_cmd(struct i2c_diolan_u2c *dev, u8 command, bool flush)
{
	dev->obuffer[dev->olen++] = command;
	dev->ocount++;
	return diolan_write_cmd(dev, flush);
}