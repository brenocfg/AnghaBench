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
struct tcs3472_data {int enable; int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCS3472_ENABLE ; 
 int TCS3472_ENABLE_AEN ; 
 int TCS3472_ENABLE_PON ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tcs3472_powerdown(struct tcs3472_data *data)
{
	int ret;
	u8 enable_mask = TCS3472_ENABLE_AEN | TCS3472_ENABLE_PON;

	mutex_lock(&data->lock);

	ret = i2c_smbus_write_byte_data(data->client, TCS3472_ENABLE,
		data->enable & ~enable_mask);
	if (!ret)
		data->enable &= ~enable_mask;

	mutex_unlock(&data->lock);

	return ret;
}