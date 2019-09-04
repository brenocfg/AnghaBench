#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int hactive; int hsync_len; int hback_porch; int hfront_porch; int vactive; int vsync_len; int vback_porch; int vfront_porch; } ;
struct ipu_di_signal_cfg {int v_to_h_sync; int hsync_pin; int vsync_pin; TYPE_1__ mode; } ;
struct ipu_di {int dummy; } ;
struct di_sync_config {int run_count; int offset_count; int cnt_polarity_gen_en; int cnt_down; int repeat_count; int cnt_clr_src; int /*<<< orphan*/  cnt_polarity_trigger_src; int /*<<< orphan*/  offset_src; int /*<<< orphan*/  run_src; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct di_sync_config*) ; 
 int /*<<< orphan*/  DI_SCR_CONF ; 
 int /*<<< orphan*/  DI_SYNC_CLK ; 
 int /*<<< orphan*/  DI_SYNC_HSYNC ; 
 int /*<<< orphan*/  DI_SYNC_INT_HSYNC ; 
 int DI_SYNC_VSYNC ; 
 int /*<<< orphan*/  ipu_di_sync_config (struct ipu_di*,struct di_sync_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_di_write (struct ipu_di*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipu_di_sync_config_noninterlaced(struct ipu_di *di,
		struct ipu_di_signal_cfg *sig, int div)
{
	u32 h_total = sig->mode.hactive + sig->mode.hsync_len +
		sig->mode.hback_porch + sig->mode.hfront_porch;
	u32 v_total = sig->mode.vactive + sig->mode.vsync_len +
		sig->mode.vback_porch + sig->mode.vfront_porch;
	struct di_sync_config cfg[] = {
		{
			/* 1: INT_HSYNC */
			.run_count = h_total - 1,
			.run_src = DI_SYNC_CLK,
		} , {
			/* PIN2: HSYNC */
			.run_count = h_total - 1,
			.run_src = DI_SYNC_CLK,
			.offset_count = div * sig->v_to_h_sync,
			.offset_src = DI_SYNC_CLK,
			.cnt_polarity_gen_en = 1,
			.cnt_polarity_trigger_src = DI_SYNC_CLK,
			.cnt_down = sig->mode.hsync_len * 2,
		} , {
			/* PIN3: VSYNC */
			.run_count = v_total - 1,
			.run_src = DI_SYNC_INT_HSYNC,
			.cnt_polarity_gen_en = 1,
			.cnt_polarity_trigger_src = DI_SYNC_INT_HSYNC,
			.cnt_down = sig->mode.vsync_len * 2,
		} , {
			/* 4: Line Active */
			.run_src = DI_SYNC_HSYNC,
			.offset_count = sig->mode.vsync_len +
					sig->mode.vback_porch,
			.offset_src = DI_SYNC_HSYNC,
			.repeat_count = sig->mode.vactive,
			.cnt_clr_src = DI_SYNC_VSYNC,
		} , {
			/* 5: Pixel Active, referenced by DC */
			.run_src = DI_SYNC_CLK,
			.offset_count = sig->mode.hsync_len +
					sig->mode.hback_porch,
			.offset_src = DI_SYNC_CLK,
			.repeat_count = sig->mode.hactive,
			.cnt_clr_src = 5, /* Line Active */
		} , {
			/* unused */
		} , {
			/* unused */
		} , {
			/* unused */
		} , {
			/* unused */
		},
	};
	/* can't use #7 and #8 for line active and pixel active counters */
	struct di_sync_config cfg_vga[] = {
		{
			/* 1: INT_HSYNC */
			.run_count = h_total - 1,
			.run_src = DI_SYNC_CLK,
		} , {
			/* 2: VSYNC */
			.run_count = v_total - 1,
			.run_src = DI_SYNC_INT_HSYNC,
		} , {
			/* 3: Line Active */
			.run_src = DI_SYNC_INT_HSYNC,
			.offset_count = sig->mode.vsync_len +
					sig->mode.vback_porch,
			.offset_src = DI_SYNC_INT_HSYNC,
			.repeat_count = sig->mode.vactive,
			.cnt_clr_src = 3 /* VSYNC */,
		} , {
			/* PIN4: HSYNC for VGA via TVEv2 on TQ MBa53 */
			.run_count = h_total - 1,
			.run_src = DI_SYNC_CLK,
			.offset_count = div * sig->v_to_h_sync + 18, /* magic value from Freescale TVE driver */
			.offset_src = DI_SYNC_CLK,
			.cnt_polarity_gen_en = 1,
			.cnt_polarity_trigger_src = DI_SYNC_CLK,
			.cnt_down = sig->mode.hsync_len * 2,
		} , {
			/* 5: Pixel Active signal to DC */
			.run_src = DI_SYNC_CLK,
			.offset_count = sig->mode.hsync_len +
					sig->mode.hback_porch,
			.offset_src = DI_SYNC_CLK,
			.repeat_count = sig->mode.hactive,
			.cnt_clr_src = 4, /* Line Active */
		} , {
			/* PIN6: VSYNC for VGA via TVEv2 on TQ MBa53 */
			.run_count = v_total - 1,
			.run_src = DI_SYNC_INT_HSYNC,
			.offset_count = 1, /* magic value from Freescale TVE driver */
			.offset_src = DI_SYNC_INT_HSYNC,
			.cnt_polarity_gen_en = 1,
			.cnt_polarity_trigger_src = DI_SYNC_INT_HSYNC,
			.cnt_down = sig->mode.vsync_len * 2,
		} , {
			/* PIN4: HSYNC for VGA via TVEv2 on i.MX53-QSB */
			.run_count = h_total - 1,
			.run_src = DI_SYNC_CLK,
			.offset_count = div * sig->v_to_h_sync + 18, /* magic value from Freescale TVE driver */
			.offset_src = DI_SYNC_CLK,
			.cnt_polarity_gen_en = 1,
			.cnt_polarity_trigger_src = DI_SYNC_CLK,
			.cnt_down = sig->mode.hsync_len * 2,
		} , {
			/* PIN6: VSYNC for VGA via TVEv2 on i.MX53-QSB */
			.run_count = v_total - 1,
			.run_src = DI_SYNC_INT_HSYNC,
			.offset_count = 1, /* magic value from Freescale TVE driver */
			.offset_src = DI_SYNC_INT_HSYNC,
			.cnt_polarity_gen_en = 1,
			.cnt_polarity_trigger_src = DI_SYNC_INT_HSYNC,
			.cnt_down = sig->mode.vsync_len * 2,
		} , {
			/* unused */
		},
	};

	ipu_di_write(di, v_total - 1, DI_SCR_CONF);
	if (sig->hsync_pin == 2 && sig->vsync_pin == 3)
		ipu_di_sync_config(di, cfg, 0, ARRAY_SIZE(cfg));
	else
		ipu_di_sync_config(di, cfg_vga, 0, ARRAY_SIZE(cfg_vga));
}