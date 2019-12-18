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
struct i2c_diolan_u2c {scalar_t__ olen; } ;

/* Variables and functions */
 scalar_t__ DIOLAN_FLUSH_LEN ; 
 int diolan_usb_transfer (struct i2c_diolan_u2c*) ; 

__attribute__((used)) static int diolan_write_cmd(struct i2c_diolan_u2c *dev, bool flush)
{
	if (flush || dev->olen >= DIOLAN_FLUSH_LEN)
		return diolan_usb_transfer(dev);
	return 0;
}