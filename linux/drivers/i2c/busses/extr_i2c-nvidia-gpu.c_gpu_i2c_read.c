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
typedef  int u32 ;
typedef  int u16 ;
struct gpu_i2c_dev {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ I2C_MST_CNTL ; 
 int I2C_MST_CNTL_BURST_SIZE_SHIFT ; 
 int I2C_MST_CNTL_CMD_READ ; 
 int I2C_MST_CNTL_CYCLE_TRIGGER ; 
 int I2C_MST_CNTL_GEN_NACK ; 
 int I2C_MST_CNTL_GEN_START ; 
 scalar_t__ I2C_MST_DATA ; 
 int gpu_i2c_check_status (struct gpu_i2c_dev*) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int,int*) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,int*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int gpu_i2c_read(struct gpu_i2c_dev *i2cd, u8 *data, u16 len)
{
	int status;
	u32 val;

	val = I2C_MST_CNTL_GEN_START | I2C_MST_CNTL_CMD_READ |
		(len << I2C_MST_CNTL_BURST_SIZE_SHIFT) |
		I2C_MST_CNTL_CYCLE_TRIGGER | I2C_MST_CNTL_GEN_NACK;
	writel(val, i2cd->regs + I2C_MST_CNTL);

	status = gpu_i2c_check_status(i2cd);
	if (status < 0)
		return status;

	val = readl(i2cd->regs + I2C_MST_DATA);
	switch (len) {
	case 1:
		data[0] = val;
		break;
	case 2:
		put_unaligned_be16(val, data);
		break;
	case 3:
		put_unaligned_be16(val >> 8, data);
		data[2] = val;
		break;
	case 4:
		put_unaligned_be32(val, data);
		break;
	default:
		break;
	}
	return status;
}