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
typedef  int /*<<< orphan*/  uint8_t ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ch7006_err (struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 
 int i2c_master_send (struct i2c_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ch7006_write(struct i2c_client *client, uint8_t addr, uint8_t val)
{
	uint8_t buf[] = {addr, val};
	int ret;

	ret = i2c_master_send(client, buf, ARRAY_SIZE(buf));
	if (ret < 0)
		ch7006_err(client, "Error %d writing to subaddress 0x%x\n",
			   ret, addr);
}