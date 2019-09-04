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
struct s6sy761_data {int /*<<< orphan*/  client; int /*<<< orphan*/  regulators; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  S6SY761_BOOT_STATUS ; 
 int S6SY761_BS_APPLICATION ; 
 int S6SY761_EVENT_INFO ; 
 int S6SY761_EVENT_SIZE ; 
 int S6SY761_EVENT_VENDOR_INFO ; 
 int S6SY761_INFO_BOOT_COMPLETE ; 
 int /*<<< orphan*/  S6SY761_MASK_TOUCH ; 
 int /*<<< orphan*/  S6SY761_READ_ONE_EVENT ; 
 int /*<<< orphan*/  S6SY761_TOUCH_FUNCTION ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_i2c_block_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int i2c_smbus_write_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s6sy761_power_on(struct s6sy761_data *sdata)
{
	u8 buffer[S6SY761_EVENT_SIZE];
	u8 event;
	int ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(sdata->regulators),
				    sdata->regulators);
	if (ret)
		return ret;

	msleep(140);

	/* double check whether the touch is functional */
	ret = i2c_smbus_read_i2c_block_data(sdata->client,
					    S6SY761_READ_ONE_EVENT,
					    S6SY761_EVENT_SIZE,
					    buffer);
	if (ret < 0)
		return ret;

	event = (buffer[0] >> 2) & 0xf;

	if ((event != S6SY761_EVENT_INFO &&
	     event != S6SY761_EVENT_VENDOR_INFO) ||
	    buffer[1] != S6SY761_INFO_BOOT_COMPLETE) {
		return -ENODEV;
	}

	ret = i2c_smbus_read_byte_data(sdata->client, S6SY761_BOOT_STATUS);
	if (ret < 0)
		return ret;

	/* for some reasons the device might be stuck in the bootloader */
	if (ret != S6SY761_BS_APPLICATION)
		return -ENODEV;

	/* enable touch functionality */
	ret = i2c_smbus_write_word_data(sdata->client,
					S6SY761_TOUCH_FUNCTION,
					S6SY761_MASK_TOUCH);
	if (ret)
		return ret;

	return 0;
}