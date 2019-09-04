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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_master_send (struct i2c_client*,char const*,int) ; 

__attribute__((used)) static int dw9714_i2c_write(struct i2c_client *client, u16 data)
{
	int ret;
	__be16 val = cpu_to_be16(data);

	ret = i2c_master_send(client, (const char *)&val, sizeof(val));
	if (ret != sizeof(val)) {
		dev_err(&client->dev, "I2C write fail\n");
		return -EIO;
	}
	return 0;
}