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
struct bma180_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMA180_CHIP_ID ; 
 int BMA180_ID_REG_VAL ; 
 int ENODEV ; 
 int bma180_set_new_data_intr_state (struct bma180_data*,int) ; 
 int bma180_set_pmode (struct bma180_data*,int) ; 
 int bma180_soft_reset (struct bma180_data*) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int bma180_chip_init(struct bma180_data *data)
{
	/* Try to read chip_id register. It must return 0x03. */
	int ret = i2c_smbus_read_byte_data(data->client, BMA180_CHIP_ID);

	if (ret < 0)
		return ret;
	if (ret != BMA180_ID_REG_VAL)
		return -ENODEV;

	ret = bma180_soft_reset(data);
	if (ret)
		return ret;
	/*
	 * No serial transaction should occur within minimum 10 us
	 * after soft_reset command
	 */
	msleep(20);

	ret = bma180_set_new_data_intr_state(data, false);
	if (ret)
		return ret;

	return bma180_set_pmode(data, false);
}