#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct videomode {int flags; int /*<<< orphan*/  vactive; int /*<<< orphan*/  hactive; int /*<<< orphan*/  vsync_len; int /*<<< orphan*/  hsync_len; int /*<<< orphan*/  vback_porch; int /*<<< orphan*/  vfront_porch; int /*<<< orphan*/  hback_porch; int /*<<< orphan*/  hfront_porch; } ;
struct malidp_hw_device {int output_color_depth; TYPE_2__* hw; } ;
struct TYPE_3__ {scalar_t__ out_depth_base; } ;
struct TYPE_4__ {TYPE_1__ map; } ;

/* Variables and functions */
 int DISPLAY_FLAGS_HSYNC_HIGH ; 
 int DISPLAY_FLAGS_INTERLACED ; 
 int DISPLAY_FLAGS_VSYNC_HIGH ; 
 scalar_t__ MALIDP500_BGND_COLOR ; 
 int MALIDP500_DC_CLEAR_MASK ; 
 int /*<<< orphan*/  MALIDP500_DC_CONTROL ; 
 int MALIDP500_DE_V_FRONTPORCH (int /*<<< orphan*/ ) ; 
 int MALIDP500_HSYNCPOL ; 
 scalar_t__ MALIDP500_TIMINGS_BASE ; 
 int MALIDP500_VSYNCPOL ; 
 int MALIDP_BGND_COLOR_B ; 
 int MALIDP_BGND_COLOR_G ; 
 int MALIDP_BGND_COLOR_R ; 
 int MALIDP_DE_DEFAULT_PREFETCH_START ; 
 int /*<<< orphan*/  MALIDP_DE_DISPLAY_FUNC ; 
 scalar_t__ MALIDP_DE_HV_ACTIVE ; 
 int MALIDP_DE_H_ACTIVE (int /*<<< orphan*/ ) ; 
 int MALIDP_DE_H_BACKPORCH (int /*<<< orphan*/ ) ; 
 int MALIDP_DE_H_FRONTPORCH (int /*<<< orphan*/ ) ; 
 int MALIDP_DE_H_SYNCWIDTH (int /*<<< orphan*/ ) ; 
 scalar_t__ MALIDP_DE_H_TIMINGS ; 
 scalar_t__ MALIDP_DE_SYNC_WIDTH ; 
 int MALIDP_DE_V_ACTIVE (int /*<<< orphan*/ ) ; 
 int MALIDP_DE_V_BACKPORCH (int /*<<< orphan*/ ) ; 
 int MALIDP_DE_V_SYNCWIDTH (int /*<<< orphan*/ ) ; 
 scalar_t__ MALIDP_DE_V_TIMINGS ; 
 int MALIDP_DISP_FUNC_ILACED ; 
 int /*<<< orphan*/  malidp_hw_clearbits (struct malidp_hw_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_hw_setbits (struct malidp_hw_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_hw_write (struct malidp_hw_device*,int,scalar_t__) ; 

__attribute__((used)) static void malidp500_modeset(struct malidp_hw_device *hwdev, struct videomode *mode)
{
	u32 val = 0;

	malidp_hw_write(hwdev, hwdev->output_color_depth,
		hwdev->hw->map.out_depth_base);
	malidp_hw_clearbits(hwdev, MALIDP500_DC_CLEAR_MASK, MALIDP500_DC_CONTROL);
	if (mode->flags & DISPLAY_FLAGS_HSYNC_HIGH)
		val |= MALIDP500_HSYNCPOL;
	if (mode->flags & DISPLAY_FLAGS_VSYNC_HIGH)
		val |= MALIDP500_VSYNCPOL;
	val |= MALIDP_DE_DEFAULT_PREFETCH_START;
	malidp_hw_setbits(hwdev, val, MALIDP500_DC_CONTROL);

	/*
	 * Mali-DP500 encodes the background color like this:
	 *    - red   @ MALIDP500_BGND_COLOR[12:0]
	 *    - green @ MALIDP500_BGND_COLOR[27:16]
	 *    - blue  @ (MALIDP500_BGND_COLOR + 4)[12:0]
	 */
	val = ((MALIDP_BGND_COLOR_G & 0xfff) << 16) |
	      (MALIDP_BGND_COLOR_R & 0xfff);
	malidp_hw_write(hwdev, val, MALIDP500_BGND_COLOR);
	malidp_hw_write(hwdev, MALIDP_BGND_COLOR_B, MALIDP500_BGND_COLOR + 4);

	val = MALIDP_DE_H_FRONTPORCH(mode->hfront_porch) |
		MALIDP_DE_H_BACKPORCH(mode->hback_porch);
	malidp_hw_write(hwdev, val, MALIDP500_TIMINGS_BASE + MALIDP_DE_H_TIMINGS);

	val = MALIDP500_DE_V_FRONTPORCH(mode->vfront_porch) |
		MALIDP_DE_V_BACKPORCH(mode->vback_porch);
	malidp_hw_write(hwdev, val, MALIDP500_TIMINGS_BASE + MALIDP_DE_V_TIMINGS);

	val = MALIDP_DE_H_SYNCWIDTH(mode->hsync_len) |
		MALIDP_DE_V_SYNCWIDTH(mode->vsync_len);
	malidp_hw_write(hwdev, val, MALIDP500_TIMINGS_BASE + MALIDP_DE_SYNC_WIDTH);

	val = MALIDP_DE_H_ACTIVE(mode->hactive) | MALIDP_DE_V_ACTIVE(mode->vactive);
	malidp_hw_write(hwdev, val, MALIDP500_TIMINGS_BASE + MALIDP_DE_HV_ACTIVE);

	if (mode->flags & DISPLAY_FLAGS_INTERLACED)
		malidp_hw_setbits(hwdev, MALIDP_DISP_FUNC_ILACED, MALIDP_DE_DISPLAY_FUNC);
	else
		malidp_hw_clearbits(hwdev, MALIDP_DISP_FUNC_ILACED, MALIDP_DE_DISPLAY_FUNC);
}