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
typedef  int u32 ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_PWR_CTRL1 ; 
 int /*<<< orphan*/  CH_PWR_CTRL2 ; 
 int /*<<< orphan*/  I2S_BLK_DEVICE_ADDRESS ; 
 int cx231xx_read_i2c_data (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int) ; 
 int cx231xx_write_i2c_data (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

int cx231xx_i2s_blk_initialize(struct cx231xx *dev)
{
	int status = 0;
	u32 value;

	status = cx231xx_read_i2c_data(dev, I2S_BLK_DEVICE_ADDRESS,
				       CH_PWR_CTRL1, 1, &value, 1);
	/* enables clock to delta-sigma and decimation filter */
	value |= 0x80;
	status = cx231xx_write_i2c_data(dev, I2S_BLK_DEVICE_ADDRESS,
					CH_PWR_CTRL1, 1, value, 1);
	/* power up all channel */
	status = cx231xx_write_i2c_data(dev, I2S_BLK_DEVICE_ADDRESS,
					CH_PWR_CTRL2, 1, 0x00, 1);

	return status;
}