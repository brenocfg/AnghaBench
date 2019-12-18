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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ISL1208_REG_DTR ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isl1208_i2c_get_dtr(struct i2c_client *client)
{
	int dtr = i2c_smbus_read_byte_data(client, ISL1208_REG_DTR);
	if (dtr < 0)
		return -EIO;

	/* dtr encodes adjustments of {-60,-40,-20,0,20,40,60} ppm */
	dtr = ((dtr & 0x3) * 20) * (dtr & (1 << 2) ? -1 : 1);

	return dtr + 100;
}