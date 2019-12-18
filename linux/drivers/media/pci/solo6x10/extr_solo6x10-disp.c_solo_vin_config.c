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
struct solo_dev {int vin_hstart; int vin_vstart; int vout_hstart; int vout_vstart; scalar_t__ type; scalar_t__ video_type; scalar_t__ video_vsize; } ;

/* Variables and functions */
 scalar_t__ SOLO_DEV_6010 ; 
 scalar_t__ SOLO_PROGRESSIVE_VSIZE ; 
 int /*<<< orphan*/  SOLO_SYS_VCLK ; 
 int /*<<< orphan*/  SOLO_VCLK_DELAY ; 
 int SOLO_VCLK_SELECT (int) ; 
 int SOLO_VCLK_VIN0001_DELAY (int /*<<< orphan*/ ) ; 
 int SOLO_VCLK_VIN0203_DELAY (int /*<<< orphan*/ ) ; 
 int SOLO_VCLK_VIN0405_DELAY (int /*<<< orphan*/ ) ; 
 int SOLO_VCLK_VIN0607_DELAY (int /*<<< orphan*/ ) ; 
 int SOLO_VCLK_VIN0809_DELAY (int /*<<< orphan*/ ) ; 
 int SOLO_VCLK_VIN1011_DELAY (int /*<<< orphan*/ ) ; 
 int SOLO_VCLK_VIN1213_DELAY (int /*<<< orphan*/ ) ; 
 int SOLO_VCLK_VIN1415_DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOLO_VI_ACT_I_P ; 
 int /*<<< orphan*/  SOLO_VI_ACT_I_S ; 
 int /*<<< orphan*/  SOLO_VI_ACT_P ; 
 int /*<<< orphan*/  SOLO_VI_CH_FORMAT ; 
 int SOLO_VI_FD_SEL_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOLO_VI_FMT_CFG ; 
 int SOLO_VI_H_START (int) ; 
 int /*<<< orphan*/  SOLO_VI_PAGE_SW ; 
 int /*<<< orphan*/  SOLO_VI_PB_ACT_H ; 
 int /*<<< orphan*/  SOLO_VI_PB_ACT_V ; 
 int /*<<< orphan*/  SOLO_VI_PB_CONFIG ; 
 int SOLO_VI_PB_HSIZE (int) ; 
 int SOLO_VI_PB_HSTART (int) ; 
 int SOLO_VI_PB_HSTOP (int) ; 
 int SOLO_VI_PB_PAL ; 
 int /*<<< orphan*/  SOLO_VI_PB_RANGE_HV ; 
 int SOLO_VI_PB_USER_MODE ; 
 int SOLO_VI_PB_VSIZE (int) ; 
 int SOLO_VI_PB_VSTART (int) ; 
 int SOLO_VI_PB_VSTOP (int) ; 
 int SOLO_VI_PROG_MASK (int /*<<< orphan*/ ) ; 
 int SOLO_VI_V_START (int) ; 
 int SOLO_VI_V_STOP (scalar_t__) ; 
 scalar_t__ SOLO_VO_FMT_TYPE_NTSC ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void solo_vin_config(struct solo_dev *solo_dev)
{
	solo_dev->vin_hstart = 8;
	solo_dev->vin_vstart = 2;

	solo_reg_write(solo_dev, SOLO_SYS_VCLK,
		       SOLO_VCLK_SELECT(2) |
		       SOLO_VCLK_VIN1415_DELAY(SOLO_VCLK_DELAY) |
		       SOLO_VCLK_VIN1213_DELAY(SOLO_VCLK_DELAY) |
		       SOLO_VCLK_VIN1011_DELAY(SOLO_VCLK_DELAY) |
		       SOLO_VCLK_VIN0809_DELAY(SOLO_VCLK_DELAY) |
		       SOLO_VCLK_VIN0607_DELAY(SOLO_VCLK_DELAY) |
		       SOLO_VCLK_VIN0405_DELAY(SOLO_VCLK_DELAY) |
		       SOLO_VCLK_VIN0203_DELAY(SOLO_VCLK_DELAY) |
		       SOLO_VCLK_VIN0001_DELAY(SOLO_VCLK_DELAY));

	solo_reg_write(solo_dev, SOLO_VI_ACT_I_P,
		       SOLO_VI_H_START(solo_dev->vin_hstart) |
		       SOLO_VI_V_START(solo_dev->vin_vstart) |
		       SOLO_VI_V_STOP(solo_dev->vin_vstart +
				      solo_dev->video_vsize));

	solo_reg_write(solo_dev, SOLO_VI_ACT_I_S,
		       SOLO_VI_H_START(solo_dev->vout_hstart) |
		       SOLO_VI_V_START(solo_dev->vout_vstart) |
		       SOLO_VI_V_STOP(solo_dev->vout_vstart +
				      solo_dev->video_vsize));

	solo_reg_write(solo_dev, SOLO_VI_ACT_P,
		       SOLO_VI_H_START(0) |
		       SOLO_VI_V_START(1) |
		       SOLO_VI_V_STOP(SOLO_PROGRESSIVE_VSIZE));

	solo_reg_write(solo_dev, SOLO_VI_CH_FORMAT,
		       SOLO_VI_FD_SEL_MASK(0) | SOLO_VI_PROG_MASK(0));

	/* On 6110, initialize mozaic darkness strength */
	if (solo_dev->type == SOLO_DEV_6010)
		solo_reg_write(solo_dev, SOLO_VI_FMT_CFG, 0);
	else
		solo_reg_write(solo_dev, SOLO_VI_FMT_CFG, 16 << 22);

	solo_reg_write(solo_dev, SOLO_VI_PAGE_SW, 2);

	if (solo_dev->video_type == SOLO_VO_FMT_TYPE_NTSC) {
		solo_reg_write(solo_dev, SOLO_VI_PB_CONFIG,
			       SOLO_VI_PB_USER_MODE);
		solo_reg_write(solo_dev, SOLO_VI_PB_RANGE_HV,
			       SOLO_VI_PB_HSIZE(858) | SOLO_VI_PB_VSIZE(246));
		solo_reg_write(solo_dev, SOLO_VI_PB_ACT_V,
			       SOLO_VI_PB_VSTART(4) |
			       SOLO_VI_PB_VSTOP(4 + 240));
	} else {
		solo_reg_write(solo_dev, SOLO_VI_PB_CONFIG,
			       SOLO_VI_PB_USER_MODE | SOLO_VI_PB_PAL);
		solo_reg_write(solo_dev, SOLO_VI_PB_RANGE_HV,
			       SOLO_VI_PB_HSIZE(864) | SOLO_VI_PB_VSIZE(294));
		solo_reg_write(solo_dev, SOLO_VI_PB_ACT_V,
			       SOLO_VI_PB_VSTART(4) |
			       SOLO_VI_PB_VSTOP(4 + 288));
	}
	solo_reg_write(solo_dev, SOLO_VI_PB_ACT_H, SOLO_VI_PB_HSTART(16) |
		       SOLO_VI_PB_HSTOP(16 + 720));
}