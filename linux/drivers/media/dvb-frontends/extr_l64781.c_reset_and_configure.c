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
struct l64781_state {int /*<<< orphan*/  i2c; } ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int reset_and_configure (struct l64781_state* state)
{
	u8 buf [] = { 0x06 };
	struct i2c_msg msg = { .addr = 0x00, .flags = 0, .buf = buf, .len = 1 };
	// NOTE: this is correct in writing to address 0x00

	return (i2c_transfer(state->i2c, &msg, 1) == 1) ? 0 : -ENODEV;
}