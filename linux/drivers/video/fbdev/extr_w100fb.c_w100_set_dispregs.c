#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int color_depth; int en_crtc; int en_graphic_req; int en_graphic_crtc; int lcd_pclk_on; int lcd_sclk_on; int total_req_graphic; unsigned long portrait_mode; int /*<<< orphan*/  req_freq; int /*<<< orphan*/  low_power_on; } ;
struct TYPE_7__ {int color_depth; int en_crtc; int en_graphic_req; int en_graphic_crtc; int lcd_pclk_on; int lcd_sclk_on; int low_power_on; int req_freq; unsigned long portrait_mode; int total_req_graphic; } ;
union graphic_ctrl_u {unsigned long val; TYPE_2__ f_w32xx; TYPE_1__ f_w100; } ;
typedef  unsigned long u32 ;
struct w100fb_par {int xres; int yres; int chip_id; TYPE_3__* mode; scalar_t__ flip; } ;
struct TYPE_10__ {unsigned long pclk_post_div; int /*<<< orphan*/  pclk_src_sel; } ;
struct TYPE_11__ {scalar_t__ val; TYPE_4__ f; } ;
struct TYPE_12__ {TYPE_5__ pclk_cntl; } ;
struct TYPE_9__ {int xres; unsigned long pixclk_divider; unsigned long pixclk_divider_rotated; int /*<<< orphan*/  pixclk_src; } ;

/* Variables and functions */
 unsigned long BITS_PER_PIXEL ; 
#define  CHIP_ID_W100 130 
#define  CHIP_ID_W3200 129 
#define  CHIP_ID_W3220 128 
 unsigned long W100_FB_BASE ; 
 scalar_t__ mmGRAPHIC_CTRL ; 
 scalar_t__ mmGRAPHIC_OFFSET ; 
 scalar_t__ mmGRAPHIC_PITCH ; 
 scalar_t__ mmPCLK_CNTL ; 
 scalar_t__ remapped_regs ; 
 TYPE_6__ w100_pwr_state ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void w100_set_dispregs(struct w100fb_par *par)
{
	unsigned long rot=0, divider, offset=0;
	union graphic_ctrl_u graphic_ctrl;

	/* See if the mode has been rotated */
	if (par->xres == par->mode->xres) {
		if (par->flip) {
			rot=3; /* 180 degree */
			offset=(par->xres * par->yres) - 1;
		} /* else 0 degree */
		divider = par->mode->pixclk_divider;
	} else {
		if (par->flip) {
			rot=2; /* 270 degree */
			offset=par->xres - 1;
		} else {
			rot=1; /* 90 degree */
			offset=par->xres * (par->yres - 1);
		}
		divider = par->mode->pixclk_divider_rotated;
	}

	graphic_ctrl.val = 0; /* w32xx doesn't like undefined bits */
	switch (par->chip_id) {
		case CHIP_ID_W100:
			graphic_ctrl.f_w100.color_depth=6;
			graphic_ctrl.f_w100.en_crtc=1;
			graphic_ctrl.f_w100.en_graphic_req=1;
			graphic_ctrl.f_w100.en_graphic_crtc=1;
			graphic_ctrl.f_w100.lcd_pclk_on=1;
			graphic_ctrl.f_w100.lcd_sclk_on=1;
			graphic_ctrl.f_w100.low_power_on=0;
			graphic_ctrl.f_w100.req_freq=0;
			graphic_ctrl.f_w100.portrait_mode=rot;

			/* Zaurus needs this */
			switch(par->xres) {
				case 240:
				case 320:
				default:
					graphic_ctrl.f_w100.total_req_graphic=0xa0;
					break;
				case 480:
				case 640:
					switch(rot) {
						case 0:  /* 0 */
						case 3:  /* 180 */
							graphic_ctrl.f_w100.low_power_on=1;
							graphic_ctrl.f_w100.req_freq=5;
						break;
						case 1:  /* 90 */
						case 2:  /* 270 */
							graphic_ctrl.f_w100.req_freq=4;
							break;
						default:
							break;
					}
					graphic_ctrl.f_w100.total_req_graphic=0xf0;
					break;
			}
			break;
		case CHIP_ID_W3200:
		case CHIP_ID_W3220:
			graphic_ctrl.f_w32xx.color_depth=6;
			graphic_ctrl.f_w32xx.en_crtc=1;
			graphic_ctrl.f_w32xx.en_graphic_req=1;
			graphic_ctrl.f_w32xx.en_graphic_crtc=1;
			graphic_ctrl.f_w32xx.lcd_pclk_on=1;
			graphic_ctrl.f_w32xx.lcd_sclk_on=1;
			graphic_ctrl.f_w32xx.low_power_on=0;
			graphic_ctrl.f_w32xx.req_freq=0;
			graphic_ctrl.f_w32xx.total_req_graphic=par->mode->xres >> 1; /* panel xres, not mode */
			graphic_ctrl.f_w32xx.portrait_mode=rot;
			break;
	}

	/* Set the pixel clock source and divider */
	w100_pwr_state.pclk_cntl.f.pclk_src_sel = par->mode->pixclk_src;
	w100_pwr_state.pclk_cntl.f.pclk_post_div = divider;
	writel((u32) (w100_pwr_state.pclk_cntl.val), remapped_regs + mmPCLK_CNTL);

	writel(graphic_ctrl.val, remapped_regs + mmGRAPHIC_CTRL);
	writel(W100_FB_BASE + ((offset * BITS_PER_PIXEL/8)&~0x03UL), remapped_regs + mmGRAPHIC_OFFSET);
	writel((par->xres*BITS_PER_PIXEL/8), remapped_regs + mmGRAPHIC_PITCH);
}