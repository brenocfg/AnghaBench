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
struct zopt2201_data {int /*<<< orphan*/  gain; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZOPT2201_LS_GAIN ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zopt2201_set_gain(struct zopt2201_data *data, u8 gain)
{
	int ret;

	ret = i2c_smbus_write_byte_data(data->client, ZOPT2201_LS_GAIN, gain);
	if (ret < 0)
		return ret;

	data->gain = gain;

	return 0;
}