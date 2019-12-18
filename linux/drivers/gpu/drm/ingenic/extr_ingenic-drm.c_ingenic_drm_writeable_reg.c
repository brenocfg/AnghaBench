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
struct device {int dummy; } ;

/* Variables and functions */
#define  JZ_REG_LCD_CMD0 134 
#define  JZ_REG_LCD_CMD1 133 
#define  JZ_REG_LCD_FID0 132 
#define  JZ_REG_LCD_FID1 131 
#define  JZ_REG_LCD_IID 130 
#define  JZ_REG_LCD_SA0 129 
#define  JZ_REG_LCD_SA1 128 

__attribute__((used)) static bool ingenic_drm_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case JZ_REG_LCD_IID:
	case JZ_REG_LCD_SA0:
	case JZ_REG_LCD_FID0:
	case JZ_REG_LCD_CMD0:
	case JZ_REG_LCD_SA1:
	case JZ_REG_LCD_FID1:
	case JZ_REG_LCD_CMD1:
		return false;
	default:
		return true;
	}
}