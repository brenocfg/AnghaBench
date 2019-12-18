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
struct sh_mobile_lcdc_panel_cfg {int /*<<< orphan*/  (* start_transfer ) (struct sh_mobile_lcdc_chan*,int /*<<< orphan*/ *) ;} ;
struct sh_mobile_lcdc_chan {int /*<<< orphan*/  sglist; TYPE_2__* lcdc; TYPE_1__* cfg; } ;
struct list_head {int dummy; } ;
struct fb_info {struct sh_mobile_lcdc_chan* par; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct sh_mobile_lcdc_panel_cfg panel_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  LDSM2R ; 
 int /*<<< orphan*/  LDSM2R_OSTRG ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write_chan (struct sh_mobile_lcdc_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_clk_on (TYPE_2__*) ; 
 unsigned int sh_mobile_lcdc_sginit (struct fb_info*,struct list_head*) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_sys_bus_ops ; 
 int /*<<< orphan*/  stub1 (struct sh_mobile_lcdc_chan*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct sh_mobile_lcdc_chan*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sh_mobile_lcdc_deferred_io(struct fb_info *info,
				       struct list_head *pagelist)
{
	struct sh_mobile_lcdc_chan *ch = info->par;
	const struct sh_mobile_lcdc_panel_cfg *panel = &ch->cfg->panel_cfg;

	/* enable clocks before accessing hardware */
	sh_mobile_lcdc_clk_on(ch->lcdc);

	/*
	 * It's possible to get here without anything on the pagelist via
	 * sh_mobile_lcdc_deferred_io_touch() or via a userspace fsync()
	 * invocation. In the former case, the acceleration routines are
	 * stepped in to when using the framebuffer console causing the
	 * workqueue to be scheduled without any dirty pages on the list.
	 *
	 * Despite this, a panel update is still needed given that the
	 * acceleration routines have their own methods for writing in
	 * that still need to be updated.
	 *
	 * The fsync() and empty pagelist case could be optimized for,
	 * but we don't bother, as any application exhibiting such
	 * behaviour is fundamentally broken anyways.
	 */
	if (!list_empty(pagelist)) {
		unsigned int nr_pages = sh_mobile_lcdc_sginit(info, pagelist);

		/* trigger panel update */
		dma_map_sg(ch->lcdc->dev, ch->sglist, nr_pages, DMA_TO_DEVICE);
		if (panel->start_transfer)
			panel->start_transfer(ch, &sh_mobile_lcdc_sys_bus_ops);
		lcdc_write_chan(ch, LDSM2R, LDSM2R_OSTRG);
		dma_unmap_sg(ch->lcdc->dev, ch->sglist, nr_pages,
			     DMA_TO_DEVICE);
	} else {
		if (panel->start_transfer)
			panel->start_transfer(ch, &sh_mobile_lcdc_sys_bus_ops);
		lcdc_write_chan(ch, LDSM2R, LDSM2R_OSTRG);
	}
}