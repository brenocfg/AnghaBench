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
 int /*<<< orphan*/  DMARD10_MODE_ACTIVE ; 
 unsigned char DMARD10_MODE_READ_OTP ; 
 unsigned char DMARD10_MODE_RESET_DATA_PATH ; 
 unsigned char DMARD10_MODE_STANDBY ; 
 unsigned char DMARD10_REG_ACTR ; 
 unsigned char DMARD10_REG_AFEM ; 
 unsigned char DMARD10_REG_MISC2 ; 
 unsigned char DMARD10_REG_PD ; 
 unsigned char DMARD10_VALUE_AFEM_AFEN_NORMAL ; 
 unsigned char DMARD10_VALUE_CKSEL_ODR_100_204 ; 
 unsigned char DMARD10_VALUE_INTC ; 
 int /*<<< orphan*/  DMARD10_VALUE_MISC2_OSCA_EN ; 
 int /*<<< orphan*/  DMARD10_VALUE_PD_RST ; 
 unsigned char DMARD10_VALUE_TAPNS_AVE_2 ; 
 int i2c_master_send (struct i2c_client*,unsigned char*,int) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmard10_reset(struct i2c_client *client)
{
	unsigned char buffer[7];
	int ret;

	/* 1. Powerdown reset */
	ret = i2c_smbus_write_byte_data(client, DMARD10_REG_PD,
						DMARD10_VALUE_PD_RST);
	if (ret < 0)
		return ret;

	/*
	 * 2. ACTR => Standby mode => Download OTP to parameter reg =>
	 *    Standby mode => Reset data path => Standby mode
	 */
	buffer[0] = DMARD10_REG_ACTR;
	buffer[1] = DMARD10_MODE_STANDBY;
	buffer[2] = DMARD10_MODE_READ_OTP;
	buffer[3] = DMARD10_MODE_STANDBY;
	buffer[4] = DMARD10_MODE_RESET_DATA_PATH;
	buffer[5] = DMARD10_MODE_STANDBY;
	ret = i2c_master_send(client, buffer, 6);
	if (ret < 0)
		return ret;

	/* 3. OSCA_EN = 1, TSTO = b'000 (INT1 = normal, TEST0 = normal) */
	ret = i2c_smbus_write_byte_data(client, DMARD10_REG_MISC2,
						DMARD10_VALUE_MISC2_OSCA_EN);
	if (ret < 0)
		return ret;

	/* 4. AFEN = 1 (AFE will powerdown after ADC) */
	buffer[0] = DMARD10_REG_AFEM;
	buffer[1] = DMARD10_VALUE_AFEM_AFEN_NORMAL;
	buffer[2] = DMARD10_VALUE_CKSEL_ODR_100_204;
	buffer[3] = DMARD10_VALUE_INTC;
	buffer[4] = DMARD10_VALUE_TAPNS_AVE_2;
	buffer[5] = 0x00; /* DLYC, no delay timing */
	buffer[6] = 0x07; /* INTD=1 push-pull, INTA=1 active high, AUTOT=1 */
	ret = i2c_master_send(client, buffer, 7);
	if (ret < 0)
		return ret;

	/* 5. Activation mode */
	ret = i2c_smbus_write_byte_data(client, DMARD10_REG_ACTR,
						DMARD10_MODE_ACTIVE);
	if (ret < 0)
		return ret;

	return 0;
}