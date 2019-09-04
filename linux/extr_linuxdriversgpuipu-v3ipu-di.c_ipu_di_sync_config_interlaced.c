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
struct ipu_di_signal_cfg {TYPE_1__ mode; } ;
struct ipu_di {int dummy; } ;
struct di_sync_config {int run_count; int run_src; int cnt_polarity_gen_en; int cnt_polarity_trigger_src; int cnt_down; int offset_count; int offset_src; int repeat_count; int /*<<< orphan*/  cnt_clr_src; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct di_sync_config*) ; 
 int /*<<< orphan*/  DI_SCR_CONF ; 
 int DI_SYNC_CLK ; 
 int /*<<< orphan*/  DI_SYNC_CNT1 ; 
 int /*<<< orphan*/  DI_SYNC_CNT4 ; 
 int /*<<< orphan*/  DI_SYNC_CNT5 ; 
 int DI_SYNC_HSYNC ; 
 int /*<<< orphan*/  ipu_di_sync_config (struct ipu_di*,struct di_sync_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_di_write (struct ipu_di*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipu_di_sync_config_interlaced(struct ipu_di *di,
		struct ipu_di_signal_cfg *sig)
{
	u32 h_total = sig->mode.hactive + sig->mode.hsync_len +
		sig->mode.hback_porch + sig->mode.hfront_porch;
	u32 v_total = sig->mode.vactive + sig->mode.vsync_len +
		sig->mode.vback_porch + sig->mode.vfront_porch;
	struct di_sync_config cfg[] = {
		{
			/* 1: internal VSYNC for each frame */
			.run_count = v_total * 2 - 1,
			.run_src = 3,			/* == counter 7 */
		}, {
			/* PIN2: HSYNC waveform */
			.run_count = h_total - 1,
			.run_src = DI_SYNC_CLK,
			.cnt_polarity_gen_en = 1,
			.cnt_polarity_trigger_src = DI_SYNC_CLK,
			.cnt_down = sig->mode.hsync_len * 2,
		}, {
			/* PIN3: VSYNC waveform */
			.run_count = v_total - 1,
			.run_src = 4,			/* == counter 7 */
			.cnt_polarity_gen_en = 1,
			.cnt_polarity_trigger_src = 4,	/* == counter 7 */
			.cnt_down = sig->mode.vsync_len * 2,
			.cnt_clr_src = DI_SYNC_CNT1,
		}, {
			/* 4: Field */
			.run_count = v_total / 2,
			.run_src = DI_SYNC_HSYNC,
			.offset_count = h_total / 2,
			.offset_src = DI_SYNC_CLK,
			.repeat_count = 2,
			.cnt_clr_src = DI_SYNC_CNT1,
		}, {
			/* 5: Active lines */
			.run_src = DI_SYNC_HSYNC,
			.offset_count = (sig->mode.vsync_len +
					 sig->mode.vback_porch) / 2,
			.offset_src = DI_SYNC_HSYNC,
			.repeat_count = sig->mode.vactive / 2,
			.cnt_clr_src = DI_SYNC_CNT4,
		}, {
			/* 6: Active pixel, referenced by DC */
			.run_src = DI_SYNC_CLK,
			.offset_count = sig->mode.hsync_len +
					sig->mode.hback_porch,
			.offset_src = DI_SYNC_CLK,
			.repeat_count = sig->mode.hactive,
			.cnt_clr_src = DI_SYNC_CNT5,
		}, {
			/* 7: Half line HSYNC */
			.run_count = h_total / 2 - 1,
			.run_src = DI_SYNC_CLK,
		}
	};

	ipu_di_sync_config(di, cfg, 0, ARRAY_SIZE(cfg));

	ipu_di_write(di, v_total / 2 - 1, DI_SCR_CONF);
}