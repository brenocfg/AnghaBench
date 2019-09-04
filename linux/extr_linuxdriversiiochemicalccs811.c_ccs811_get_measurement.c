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
struct ccs811_data {int /*<<< orphan*/  buffer; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCS811_ALG_RESULT_DATA ; 
 int /*<<< orphan*/  CCS811_STATUS ; 
 int CCS811_STATUS_DATA_READY ; 
 int EIO ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_i2c_block_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int ccs811_get_measurement(struct ccs811_data *data)
{
	int ret, tries = 11;

	/* Maximum waiting time: 1s, as measurements are made every second */
	while (tries-- > 0) {
		ret = i2c_smbus_read_byte_data(data->client, CCS811_STATUS);
		if (ret < 0)
			return ret;

		if ((ret & CCS811_STATUS_DATA_READY) || tries == 0)
			break;
		msleep(100);
	}
	if (!(ret & CCS811_STATUS_DATA_READY))
		return -EIO;

	return i2c_smbus_read_i2c_block_data(data->client,
					    CCS811_ALG_RESULT_DATA, 8,
					    (char *)&data->buffer);
}