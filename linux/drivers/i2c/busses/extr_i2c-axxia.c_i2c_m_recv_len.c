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
struct i2c_msg {int flags; } ;

/* Variables and functions */
 int I2C_M_RECV_LEN ; 

__attribute__((used)) static int i2c_m_recv_len(const struct i2c_msg *msg)
{
	return (msg->flags & I2C_M_RECV_LEN) != 0;
}