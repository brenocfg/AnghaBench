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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int i2c_master_recv (struct i2c_client*,int*,int) ; 
 int i2c_master_send (struct i2c_client*,int*,int) ; 

__attribute__((used)) static int ov772x_read(struct i2c_client *client, u8 addr)
{
	int ret;
	u8 val;

	ret = i2c_master_send(client, &addr, 1);
	if (ret < 0)
		return ret;
	ret = i2c_master_recv(client, &val, 1);
	if (ret < 0)
		return ret;

	return val;
}