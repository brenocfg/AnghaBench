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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VAR8 (int,int) ; 
 int /*<<< orphan*/  mt9t112_mcu_write (int,struct i2c_client const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt9t112_auto_focus_trigger(const struct i2c_client *client)
{
	int ret;

	mt9t112_mcu_write(ret, client, VAR8(12, 25), 0x01);

	return ret;
}