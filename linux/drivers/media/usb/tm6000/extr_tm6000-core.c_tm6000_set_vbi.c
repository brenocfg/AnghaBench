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
struct tm6000_core {scalar_t__ dev_type; } ;

/* Variables and functions */
 scalar_t__ TM6010 ; 
 int /*<<< orphan*/  TM6010_REQ07_R3F_RESET ; 
 int /*<<< orphan*/  TM6010_REQ07_R40_TELETEXT_VBI_CODE0 ; 
 int /*<<< orphan*/  TM6010_REQ07_R41_TELETEXT_VBI_CODE1 ; 
 int /*<<< orphan*/  TM6010_REQ07_R42_VBI_DATA_HIGH_LEVEL ; 
 int /*<<< orphan*/  TM6010_REQ07_R43_VBI_DATA_TYPE_LINE7 ; 
 int /*<<< orphan*/  TM6010_REQ07_R44_VBI_DATA_TYPE_LINE8 ; 
 int /*<<< orphan*/  TM6010_REQ07_R45_VBI_DATA_TYPE_LINE9 ; 
 int /*<<< orphan*/  TM6010_REQ07_R46_VBI_DATA_TYPE_LINE10 ; 
 int /*<<< orphan*/  TM6010_REQ07_R47_VBI_DATA_TYPE_LINE11 ; 
 int /*<<< orphan*/  TM6010_REQ07_R48_VBI_DATA_TYPE_LINE12 ; 
 int /*<<< orphan*/  TM6010_REQ07_R49_VBI_DATA_TYPE_LINE13 ; 
 int /*<<< orphan*/  TM6010_REQ07_R4A_VBI_DATA_TYPE_LINE14 ; 
 int /*<<< orphan*/  TM6010_REQ07_R4B_VBI_DATA_TYPE_LINE15 ; 
 int /*<<< orphan*/  TM6010_REQ07_R4C_VBI_DATA_TYPE_LINE16 ; 
 int /*<<< orphan*/  TM6010_REQ07_R4D_VBI_DATA_TYPE_LINE17 ; 
 int /*<<< orphan*/  TM6010_REQ07_R4E_VBI_DATA_TYPE_LINE18 ; 
 int /*<<< orphan*/  TM6010_REQ07_R4F_VBI_DATA_TYPE_LINE19 ; 
 int /*<<< orphan*/  TM6010_REQ07_R50_VBI_DATA_TYPE_LINE20 ; 
 int /*<<< orphan*/  TM6010_REQ07_R51_VBI_DATA_TYPE_LINE21 ; 
 int /*<<< orphan*/  TM6010_REQ07_R52_VBI_DATA_TYPE_LINE22 ; 
 int /*<<< orphan*/  TM6010_REQ07_R53_VBI_DATA_TYPE_LINE23 ; 
 int /*<<< orphan*/  TM6010_REQ07_R54_VBI_DATA_TYPE_RLINES ; 
 int /*<<< orphan*/  TM6010_REQ07_R55_VBI_LOOP_FILTER_GAIN ; 
 int /*<<< orphan*/  TM6010_REQ07_R56_VBI_LOOP_FILTER_I_GAIN ; 
 int /*<<< orphan*/  TM6010_REQ07_R57_VBI_LOOP_FILTER_P_GAIN ; 
 int /*<<< orphan*/  TM6010_REQ07_R58_VBI_CAPTION_DTO1 ; 
 int /*<<< orphan*/  TM6010_REQ07_R59_VBI_CAPTION_DTO0 ; 
 int /*<<< orphan*/  TM6010_REQ07_R5A_VBI_TELETEXT_DTO1 ; 
 int /*<<< orphan*/  TM6010_REQ07_R5B_VBI_TELETEXT_DTO0 ; 
 int /*<<< orphan*/  tm6000_set_reg (struct tm6000_core*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tm6000_set_vbi(struct tm6000_core *dev)
{
	/*
	 * FIXME:
	 * VBI lines and start/end are different between 60Hz and 50Hz
	 * So, it is very likely that we need to change the config to
	 * something that takes it into account, doing something different
	 * if (dev->norm & V4L2_STD_525_60)
	 */

	if (dev->dev_type == TM6010) {
		tm6000_set_reg(dev, TM6010_REQ07_R3F_RESET, 0x01);
		tm6000_set_reg(dev, TM6010_REQ07_R41_TELETEXT_VBI_CODE1, 0x27);
		tm6000_set_reg(dev, TM6010_REQ07_R42_VBI_DATA_HIGH_LEVEL, 0x55);
		tm6000_set_reg(dev, TM6010_REQ07_R43_VBI_DATA_TYPE_LINE7, 0x66);
		tm6000_set_reg(dev, TM6010_REQ07_R44_VBI_DATA_TYPE_LINE8, 0x66);
		tm6000_set_reg(dev, TM6010_REQ07_R45_VBI_DATA_TYPE_LINE9, 0x66);
		tm6000_set_reg(dev,
			TM6010_REQ07_R46_VBI_DATA_TYPE_LINE10, 0x66);
		tm6000_set_reg(dev,
			TM6010_REQ07_R47_VBI_DATA_TYPE_LINE11, 0x66);
		tm6000_set_reg(dev,
			TM6010_REQ07_R48_VBI_DATA_TYPE_LINE12, 0x66);
		tm6000_set_reg(dev,
			TM6010_REQ07_R49_VBI_DATA_TYPE_LINE13, 0x66);
		tm6000_set_reg(dev,
			TM6010_REQ07_R4A_VBI_DATA_TYPE_LINE14, 0x66);
		tm6000_set_reg(dev,
			TM6010_REQ07_R4B_VBI_DATA_TYPE_LINE15, 0x66);
		tm6000_set_reg(dev,
			TM6010_REQ07_R4C_VBI_DATA_TYPE_LINE16, 0x66);
		tm6000_set_reg(dev,
			TM6010_REQ07_R4D_VBI_DATA_TYPE_LINE17, 0x66);
		tm6000_set_reg(dev,
			TM6010_REQ07_R4E_VBI_DATA_TYPE_LINE18, 0x66);
		tm6000_set_reg(dev,
			TM6010_REQ07_R4F_VBI_DATA_TYPE_LINE19, 0x66);
		tm6000_set_reg(dev,
			TM6010_REQ07_R50_VBI_DATA_TYPE_LINE20, 0x66);
		tm6000_set_reg(dev,
			TM6010_REQ07_R51_VBI_DATA_TYPE_LINE21, 0x66);
		tm6000_set_reg(dev,
			TM6010_REQ07_R52_VBI_DATA_TYPE_LINE22, 0x66);
		tm6000_set_reg(dev,
			TM6010_REQ07_R53_VBI_DATA_TYPE_LINE23, 0x00);
		tm6000_set_reg(dev,
			TM6010_REQ07_R54_VBI_DATA_TYPE_RLINES, 0x00);
		tm6000_set_reg(dev,
			TM6010_REQ07_R55_VBI_LOOP_FILTER_GAIN, 0x01);
		tm6000_set_reg(dev,
			TM6010_REQ07_R56_VBI_LOOP_FILTER_I_GAIN, 0x00);
		tm6000_set_reg(dev,
			TM6010_REQ07_R57_VBI_LOOP_FILTER_P_GAIN, 0x02);
		tm6000_set_reg(dev, TM6010_REQ07_R58_VBI_CAPTION_DTO1, 0x35);
		tm6000_set_reg(dev, TM6010_REQ07_R59_VBI_CAPTION_DTO0, 0xa0);
		tm6000_set_reg(dev, TM6010_REQ07_R5A_VBI_TELETEXT_DTO1, 0x11);
		tm6000_set_reg(dev, TM6010_REQ07_R5B_VBI_TELETEXT_DTO0, 0x4c);
		tm6000_set_reg(dev, TM6010_REQ07_R40_TELETEXT_VBI_CODE0, 0x01);
		tm6000_set_reg(dev, TM6010_REQ07_R3F_RESET, 0x00);
	}
}