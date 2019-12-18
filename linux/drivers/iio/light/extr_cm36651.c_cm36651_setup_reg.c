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
struct cm36651_data {int* cs_ctrl_regs; int* ps_ctrl_regs; struct i2c_client* ps_client; struct i2c_client* client; } ;

/* Variables and functions */
 int CM36651_ALS_DISABLE ; 
 int CM36651_ALS_ENABLE ; 
 int CM36651_ALS_THRES ; 
 size_t CM36651_CS_CONF1 ; 
 size_t CM36651_CS_CONF2 ; 
 int CM36651_CS_CONF2_DEFAULT_BIT ; 
 int CM36651_CS_CONF_REG_NUM ; 
 size_t CM36651_PS_CANC ; 
 int CM36651_PS_CANC_DEFAULT ; 
 size_t CM36651_PS_CONF1 ; 
 size_t CM36651_PS_CONF2 ; 
 int CM36651_PS_DIR_INT ; 
 int CM36651_PS_DISABLE ; 
 int CM36651_PS_ENABLE ; 
 int CM36651_PS_HYS2 ; 
 int CM36651_PS_INITIAL_THD ; 
 int CM36651_PS_IT2 ; 
 int CM36651_PS_REG_NUM ; 
 int CM36651_PS_SMART_PERS_EN ; 
 size_t CM36651_PS_THD ; 
 size_t* cm36651_cs_reg ; 
 size_t* cm36651_ps_reg ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,size_t,int) ; 

__attribute__((used)) static int cm36651_setup_reg(struct cm36651_data *cm36651)
{
	struct i2c_client *client = cm36651->client;
	struct i2c_client *ps_client = cm36651->ps_client;
	int i, ret;

	/* CS initialization */
	cm36651->cs_ctrl_regs[CM36651_CS_CONF1] = CM36651_ALS_ENABLE |
							     CM36651_ALS_THRES;
	cm36651->cs_ctrl_regs[CM36651_CS_CONF2] = CM36651_CS_CONF2_DEFAULT_BIT;

	for (i = 0; i < CM36651_CS_CONF_REG_NUM; i++) {
		ret = i2c_smbus_write_byte_data(client, cm36651_cs_reg[i],
						     cm36651->cs_ctrl_regs[i]);
		if (ret < 0)
			return ret;
	}

	/* PS initialization */
	cm36651->ps_ctrl_regs[CM36651_PS_CONF1] = CM36651_PS_ENABLE |
								CM36651_PS_IT2;
	cm36651->ps_ctrl_regs[CM36651_PS_THD] = CM36651_PS_INITIAL_THD;
	cm36651->ps_ctrl_regs[CM36651_PS_CANC] = CM36651_PS_CANC_DEFAULT;
	cm36651->ps_ctrl_regs[CM36651_PS_CONF2] = CM36651_PS_HYS2 |
				CM36651_PS_DIR_INT | CM36651_PS_SMART_PERS_EN;

	for (i = 0; i < CM36651_PS_REG_NUM; i++) {
		ret = i2c_smbus_write_byte_data(ps_client, cm36651_ps_reg[i],
						     cm36651->ps_ctrl_regs[i]);
		if (ret < 0)
			return ret;
	}

	/* Set shutdown mode */
	ret = i2c_smbus_write_byte_data(client, CM36651_CS_CONF1,
							  CM36651_ALS_DISABLE);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_write_byte_data(cm36651->ps_client,
					 CM36651_PS_CONF1, CM36651_PS_DISABLE);
	if (ret < 0)
		return ret;

	return 0;
}