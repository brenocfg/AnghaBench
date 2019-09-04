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
struct cm32181_chip {int* conf_regs; int /*<<< orphan*/  calibscale; struct i2c_client* client; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CM32181_CALIBSCALE_DEFAULT ; 
 int CM32181_CMD_ALS_ENABLE ; 
 int CM32181_CMD_ALS_IT_DEFAULT ; 
 int CM32181_CMD_ALS_SM_DEFAULT ; 
 int CM32181_CONF_REG_NUM ; 
 size_t CM32181_REG_ADDR_CMD ; 
 int /*<<< orphan*/  CM32181_REG_ADDR_ID ; 
 int ENODEV ; 
 int /*<<< orphan*/ * cm32181_reg ; 
 int i2c_smbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_word_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cm32181_reg_init(struct cm32181_chip *cm32181)
{
	struct i2c_client *client = cm32181->client;
	int i;
	s32 ret;

	ret = i2c_smbus_read_word_data(client, CM32181_REG_ADDR_ID);
	if (ret < 0)
		return ret;

	/* check device ID */
	if ((ret & 0xFF) != 0x81)
		return -ENODEV;

	/* Default Values */
	cm32181->conf_regs[CM32181_REG_ADDR_CMD] = CM32181_CMD_ALS_ENABLE |
			CM32181_CMD_ALS_IT_DEFAULT | CM32181_CMD_ALS_SM_DEFAULT;
	cm32181->calibscale = CM32181_CALIBSCALE_DEFAULT;

	/* Initialize registers*/
	for (i = 0; i < CM32181_CONF_REG_NUM; i++) {
		ret = i2c_smbus_write_word_data(client, cm32181_reg[i],
			cm32181->conf_regs[i]);
		if (ret < 0)
			return ret;
	}

	return 0;
}