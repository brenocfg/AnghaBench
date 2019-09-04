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
typedef  size_t u8 ;
struct stm32f7_i2c_msg {int size; size_t* smbus_buf; } ;
struct stm32f7_i2c_dev {int /*<<< orphan*/  dev; scalar_t__ base; struct stm32f7_i2c_msg f7_msg; } ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
#define  I2C_SMBUS_BLOCK_DATA 133 
#define  I2C_SMBUS_BLOCK_PROC_CALL 132 
#define  I2C_SMBUS_BYTE 131 
#define  I2C_SMBUS_BYTE_DATA 130 
#define  I2C_SMBUS_PROC_CALL 129 
#define  I2C_SMBUS_WORD_DATA 128 
 scalar_t__ STM32F7_I2C_PECR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 size_t readl_relaxed (scalar_t__) ; 

__attribute__((used)) static int stm32f7_i2c_smbus_check_pec(struct stm32f7_i2c_dev *i2c_dev)
{
	struct stm32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	u8 count, internal_pec, received_pec;

	internal_pec = readl_relaxed(i2c_dev->base + STM32F7_I2C_PECR);

	switch (f7_msg->size) {
	case I2C_SMBUS_BYTE:
	case I2C_SMBUS_BYTE_DATA:
		received_pec = f7_msg->smbus_buf[1];
		break;
	case I2C_SMBUS_WORD_DATA:
	case I2C_SMBUS_PROC_CALL:
		received_pec = f7_msg->smbus_buf[2];
		break;
	case I2C_SMBUS_BLOCK_DATA:
	case I2C_SMBUS_BLOCK_PROC_CALL:
		count = f7_msg->smbus_buf[0];
		received_pec = f7_msg->smbus_buf[count];
		break;
	default:
		dev_err(i2c_dev->dev, "Unsupported smbus protocol for PEC\n");
		return -EINVAL;
	}

	if (internal_pec != received_pec) {
		dev_err(i2c_dev->dev, "Bad PEC 0x%02x vs. 0x%02x\n",
			internal_pec, received_pec);
		return -EBADMSG;
	}

	return 0;
}