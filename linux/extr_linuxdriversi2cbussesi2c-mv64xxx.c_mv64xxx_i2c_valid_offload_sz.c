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
struct i2c_msg {int len; } ;

/* Variables and functions */

__attribute__((used)) static bool
mv64xxx_i2c_valid_offload_sz(struct i2c_msg *msg)
{
	return msg->len <= 8 && msg->len >= 1;
}