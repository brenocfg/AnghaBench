#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sh_mobile_lcdc_panel_cfg {int /*<<< orphan*/  (* display_off ) () ;} ;
struct sh_mobile_lcdc_chan {TYPE_3__* tx_dev; TYPE_1__* cfg; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* display_off ) (TYPE_3__*) ;} ;
struct TYPE_4__ {struct sh_mobile_lcdc_panel_cfg panel_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

__attribute__((used)) static void sh_mobile_lcdc_display_off(struct sh_mobile_lcdc_chan *ch)
{
	const struct sh_mobile_lcdc_panel_cfg *panel = &ch->cfg->panel_cfg;

	if (panel->display_off)
		panel->display_off();

	if (ch->tx_dev)
		ch->tx_dev->ops->display_off(ch->tx_dev);
}