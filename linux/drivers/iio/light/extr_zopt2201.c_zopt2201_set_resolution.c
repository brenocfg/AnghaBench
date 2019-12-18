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
struct zopt2201_data {int rate; int res; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZOPT2201_LS_MEAS_RATE ; 
 int ZOPT2201_MEAS_RES_SHIFT ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int zopt2201_set_resolution(struct zopt2201_data *data, u8 res)
{
	int ret;

	ret = i2c_smbus_write_byte_data(data->client, ZOPT2201_LS_MEAS_RATE,
					(res << ZOPT2201_MEAS_RES_SHIFT) |
					data->rate);
	if (ret < 0)
		return ret;

	data->res = res;

	return 0;
}