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
typedef  scalar_t__ u32 ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFE_CTRL_C2HH_SRC_CTRL ; 
 int /*<<< orphan*/  AUD_IO_CTRL ; 
 scalar_t__ DIF_USE_BASEBAND ; 
 scalar_t__ V4L2_STD_MN ; 
 scalar_t__ V4L2_STD_PAL_D ; 
 scalar_t__ V4L2_STD_PAL_I ; 
 scalar_t__ V4L2_STD_SECAM ; 
 scalar_t__ V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  VID_BLK_I2C_ADDRESS ; 
 int cx231xx_reg_mask_write (struct cx231xx*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int) ; 

int cx231xx_dif_configure_C2HH_for_low_IF(struct cx231xx *dev, u32 mode,
					  u32 function_mode, u32 standard)
{
	int status = 0;


	if (mode == V4L2_TUNER_RADIO) {
		/* C2HH */
		/* lo if big signal */
		status = cx231xx_reg_mask_write(dev,
				VID_BLK_I2C_ADDRESS, 32,
				AFE_CTRL_C2HH_SRC_CTRL, 30, 31, 0x1);
		/* FUNC_MODE = DIF */
		status = cx231xx_reg_mask_write(dev,
				VID_BLK_I2C_ADDRESS, 32,
				AFE_CTRL_C2HH_SRC_CTRL, 23, 24, function_mode);
		/* IF_MODE */
		status = cx231xx_reg_mask_write(dev,
				VID_BLK_I2C_ADDRESS, 32,
				AFE_CTRL_C2HH_SRC_CTRL, 15, 22, 0xFF);
		/* no inv */
		status = cx231xx_reg_mask_write(dev,
				VID_BLK_I2C_ADDRESS, 32,
				AFE_CTRL_C2HH_SRC_CTRL, 9, 9, 0x1);
	} else if (standard != DIF_USE_BASEBAND) {
		if (standard & V4L2_STD_MN) {
			/* lo if big signal */
			status = cx231xx_reg_mask_write(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 30, 31, 0x1);
			/* FUNC_MODE = DIF */
			status = cx231xx_reg_mask_write(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 23, 24,
					function_mode);
			/* IF_MODE */
			status = cx231xx_reg_mask_write(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 15, 22, 0xb);
			/* no inv */
			status = cx231xx_reg_mask_write(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 9, 9, 0x1);
			/* 0x124, AUD_CHAN1_SRC = 0x3 */
			status = cx231xx_reg_mask_write(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AUD_IO_CTRL, 0, 31, 0x00000003);
		} else if ((standard == V4L2_STD_PAL_I) |
			(standard & V4L2_STD_PAL_D) |
			(standard & V4L2_STD_SECAM)) {
			/* C2HH setup */
			/* lo if big signal */
			status = cx231xx_reg_mask_write(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 30, 31, 0x1);
			/* FUNC_MODE = DIF */
			status = cx231xx_reg_mask_write(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 23, 24,
					function_mode);
			/* IF_MODE */
			status = cx231xx_reg_mask_write(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 15, 22, 0xF);
			/* no inv */
			status = cx231xx_reg_mask_write(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 9, 9, 0x1);
		} else {
			/* default PAL BG */
			/* C2HH setup */
			/* lo if big signal */
			status = cx231xx_reg_mask_write(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 30, 31, 0x1);
			/* FUNC_MODE = DIF */
			status = cx231xx_reg_mask_write(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 23, 24,
					function_mode);
			/* IF_MODE */
			status = cx231xx_reg_mask_write(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 15, 22, 0xE);
			/* no inv */
			status = cx231xx_reg_mask_write(dev,
					VID_BLK_I2C_ADDRESS, 32,
					AFE_CTRL_C2HH_SRC_CTRL, 9, 9, 0x1);
		}
	}

	return status;
}