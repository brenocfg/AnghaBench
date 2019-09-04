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
struct mcp4725_data {int dac_value; int powerdown; int /*<<< orphan*/  client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_get_clientdata (int /*<<< orphan*/ ) ; 
 int i2c_master_send (int /*<<< orphan*/ ,int*,int) ; 
 struct mcp4725_data* iio_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static int mcp4725_resume(struct device *dev)
{
	struct mcp4725_data *data = iio_priv(i2c_get_clientdata(
		to_i2c_client(dev)));
	u8 outbuf[2];

	/* restore previous DAC value */
	outbuf[0] = (data->dac_value >> 8) & 0xf;
	outbuf[1] = data->dac_value & 0xff;
	data->powerdown = false;

	return i2c_master_send(data->client, outbuf, 2);
}