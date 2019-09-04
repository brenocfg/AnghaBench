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
typedef  int u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int MAX_HEIGHT ; 
 int MAX_WIDTH ; 
 int /*<<< orphan*/  VAR (int,int) ; 
 int /*<<< orphan*/  VAR8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9t112_mcu_write (int,struct i2c_client const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt9t112_set_a_frame_size(const struct i2c_client *client,
				    u16 width, u16 height)
{
	int ret;
	u16 wstart = (MAX_WIDTH - width) / 2;
	u16 hstart = (MAX_HEIGHT - height) / 2;

	/* (Context A) Image Width/Height. */
	mt9t112_mcu_write(ret, client, VAR(26, 0), width);
	mt9t112_mcu_write(ret, client, VAR(26, 2), height);

	/* (Context A) Output Width/Height. */
	mt9t112_mcu_write(ret, client, VAR(18, 43), 8 + width);
	mt9t112_mcu_write(ret, client, VAR(18, 45), 8 + height);

	/* (Context A) Start Row/Column. */
	mt9t112_mcu_write(ret, client, VAR(18, 2), 4 + hstart);
	mt9t112_mcu_write(ret, client, VAR(18, 4), 4 + wstart);

	/* (Context A) End Row/Column. */
	mt9t112_mcu_write(ret, client, VAR(18, 6), 11 + height + hstart);
	mt9t112_mcu_write(ret, client, VAR(18, 8), 11 + width  + wstart);

	mt9t112_mcu_write(ret, client, VAR8(1, 0), 0x06);

	return ret;
}