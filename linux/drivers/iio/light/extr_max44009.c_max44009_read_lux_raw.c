#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct max44009_data {TYPE_1__* client; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  loreg ;
typedef  int /*<<< orphan*/  lo ;
typedef  int /*<<< orphan*/  hireg ;
typedef  int /*<<< orphan*/  hi ;
struct TYPE_2__ {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int MAX44009_READ_LUX_XFER_LEN ; 
 int /*<<< orphan*/  MAX44009_REG_LUX_HI ; 
 int /*<<< orphan*/  MAX44009_REG_LUX_LO ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int max44009_lux_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max44009_read_lux_raw(struct max44009_data *data)
{
	int ret;
	u8 hireg = MAX44009_REG_LUX_HI;
	u8 loreg = MAX44009_REG_LUX_LO;
	u8 lo = 0;
	u8 hi = 0;

	struct i2c_msg msgs[] = {
		{
			.addr = data->client->addr,
			.flags = 0,
			.len = sizeof(hireg),
			.buf = &hireg,
		},
		{
			.addr = data->client->addr,
			.flags = I2C_M_RD,
			.len = sizeof(hi),
			.buf = &hi,
		},
		{
			.addr = data->client->addr,
			.flags = 0,
			.len = sizeof(loreg),
			.buf = &loreg,
		},
		{
			.addr = data->client->addr,
			.flags = I2C_M_RD,
			.len = sizeof(lo),
			.buf = &lo,
		}
	};

	/*
	 * Use i2c_transfer instead of smbus read because i2c_transfer
	 * does NOT use a stop bit between address write and data read.
	 * Using a stop bit causes disjoint upper/lower byte reads and
	 * reduces accuracy.
	 */
	ret = i2c_transfer(data->client->adapter,
			   msgs, MAX44009_READ_LUX_XFER_LEN);

	if (ret != MAX44009_READ_LUX_XFER_LEN)
		return -EIO;

	return max44009_lux_raw(hi, lo);
}