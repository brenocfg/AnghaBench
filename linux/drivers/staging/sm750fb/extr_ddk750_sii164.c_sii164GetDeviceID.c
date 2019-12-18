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

/* Variables and functions */
 int /*<<< orphan*/  SII164_DEVICE_ID_HIGH ; 
 int /*<<< orphan*/  SII164_DEVICE_ID_LOW ; 
 int /*<<< orphan*/  SII164_I2C_ADDRESS ; 
 scalar_t__ i2cReadReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned short sii164GetDeviceID(void)
{
	unsigned short deviceID;

	deviceID = ((unsigned short)i2cReadReg(SII164_I2C_ADDRESS, SII164_DEVICE_ID_HIGH) << 8) |
		    (unsigned short)i2cReadReg(SII164_I2C_ADDRESS, SII164_DEVICE_ID_LOW);

	return deviceID;
}