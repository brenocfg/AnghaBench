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
struct ltc2497_st {scalar_t__ addr_prev; int /*<<< orphan*/  buf; int /*<<< orphan*/  time_prev; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  LTC2497_CONVERSION_TIME_MS ; 
 scalar_t__ LTC2497_ENABLE ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_master_recv (struct i2c_client*,char*,int) ; 
 int i2c_smbus_write_byte (struct i2c_client*,scalar_t__) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int ltc2497_wait_conv (struct ltc2497_st*) ; 
 scalar_t__ msleep_interruptible (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltc2497_read(struct ltc2497_st *st, u8 address, int *val)
{
	struct i2c_client *client = st->client;
	int ret;

	ret = ltc2497_wait_conv(st);
	if (ret < 0)
		return ret;

	if (ret || st->addr_prev != address) {
		ret = i2c_smbus_write_byte(st->client,
					   LTC2497_ENABLE | address);
		if (ret < 0)
			return ret;
		st->addr_prev = address;
		if (msleep_interruptible(LTC2497_CONVERSION_TIME_MS))
			return -ERESTARTSYS;
	}
	ret = i2c_master_recv(client, (char *)&st->buf, 3);
	if (ret < 0)  {
		dev_err(&client->dev, "i2c_master_recv failed\n");
		return ret;
	}
	st->time_prev = ktime_get();

	/* convert and shift the result,
	 * and finally convert from offset binary to signed integer
	 */
	*val = (be32_to_cpu(st->buf) >> 14) - (1 << 17);

	return ret;
}