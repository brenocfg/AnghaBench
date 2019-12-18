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
struct sh_mobile_lcdc_chan {TYPE_1__* info; } ;
struct TYPE_2__ {scalar_t__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  unregister_framebuffer (TYPE_1__*) ; 

__attribute__((used)) static void
sh_mobile_lcdc_channel_fb_unregister(struct sh_mobile_lcdc_chan *ch)
{
	if (ch->info && ch->info->dev)
		unregister_framebuffer(ch->info);
}