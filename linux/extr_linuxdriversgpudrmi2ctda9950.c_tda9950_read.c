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
typedef  scalar_t__ u8 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int tda9950_read_range (struct i2c_client*,scalar_t__,scalar_t__*,int) ; 

__attribute__((used)) static u8 tda9950_read(struct i2c_client *client, u8 addr)
{
	int ret;
	u8 val;

	ret = tda9950_read_range(client, addr, &val, 1);
	if (ret < 0)
		val = 0;

	return val;
}