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
struct em28xx {int dummy; } ;

/* Variables and functions */
 int BLUE_BALANCE_DEFAULT ; 
 int BRIGHTNESS_DEFAULT ; 
 int CONTRAST_DEFAULT ; 
 int /*<<< orphan*/  EM28XX_R14_GAMMA ; 
 int /*<<< orphan*/  EM28XX_R15_RGAIN ; 
 int /*<<< orphan*/  EM28XX_R16_GGAIN ; 
 int /*<<< orphan*/  EM28XX_R17_BGAIN ; 
 int /*<<< orphan*/  EM28XX_R18_ROFFSET ; 
 int /*<<< orphan*/  EM28XX_R19_GOFFSET ; 
 int /*<<< orphan*/  EM28XX_R1A_BOFFSET ; 
 int /*<<< orphan*/  EM28XX_R20_YGAIN ; 
 int /*<<< orphan*/  EM28XX_R21_YOFFSET ; 
 int /*<<< orphan*/  EM28XX_R22_UVGAIN ; 
 int /*<<< orphan*/  EM28XX_R23_UOFFSET ; 
 int /*<<< orphan*/  EM28XX_R24_VOFFSET ; 
 int /*<<< orphan*/  EM28XX_R25_SHARPNESS ; 
 int RED_BALANCE_DEFAULT ; 
 int SATURATION_DEFAULT ; 
 int SHARPNESS_DEFAULT ; 
 int em28xx_write_reg (struct em28xx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int em28xx_colorlevels_set_default(struct em28xx *dev)
{
	em28xx_write_reg(dev, EM28XX_R20_YGAIN, CONTRAST_DEFAULT);
	em28xx_write_reg(dev, EM28XX_R21_YOFFSET, BRIGHTNESS_DEFAULT);
	em28xx_write_reg(dev, EM28XX_R22_UVGAIN, SATURATION_DEFAULT);
	em28xx_write_reg(dev, EM28XX_R23_UOFFSET, BLUE_BALANCE_DEFAULT);
	em28xx_write_reg(dev, EM28XX_R24_VOFFSET, RED_BALANCE_DEFAULT);
	em28xx_write_reg(dev, EM28XX_R25_SHARPNESS, SHARPNESS_DEFAULT);

	em28xx_write_reg(dev, EM28XX_R14_GAMMA, 0x20);
	em28xx_write_reg(dev, EM28XX_R15_RGAIN, 0x20);
	em28xx_write_reg(dev, EM28XX_R16_GGAIN, 0x20);
	em28xx_write_reg(dev, EM28XX_R17_BGAIN, 0x20);
	em28xx_write_reg(dev, EM28XX_R18_ROFFSET, 0x00);
	em28xx_write_reg(dev, EM28XX_R19_GOFFSET, 0x00);
	return em28xx_write_reg(dev, EM28XX_R1A_BOFFSET, 0x00);
}