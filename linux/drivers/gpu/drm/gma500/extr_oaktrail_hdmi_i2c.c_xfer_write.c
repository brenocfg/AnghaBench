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
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int xfer_write(struct i2c_adapter *adap, struct i2c_msg *pmsg)
{
	/*
	 * XXX: i2c write seems isn't useful for EDID probe, don't do anything
	 */
	return 0;
}