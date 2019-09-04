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
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  regval ;

/* Variables and functions */
 int EIO ; 
 int i2c_master_send (struct i2c_client*,char*,int) ; 

__attribute__((used)) static int lv0104cs_write_reg(struct i2c_client *client, u8 regval)
{
	int ret;

	ret = i2c_master_send(client, (char *)&regval, sizeof(regval));
	if (ret < 0)
		return ret;
	if (ret != sizeof(regval))
		return -EIO;

	return 0;
}