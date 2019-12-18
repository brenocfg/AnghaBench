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
struct sh_mobile_lcdc_chan {TYPE_1__* cfg; } ;
struct TYPE_2__ {scalar_t__ chan; } ;

/* Variables and functions */
 scalar_t__ LCDC_CHAN_SUBLCD ; 

__attribute__((used)) static int lcdc_chan_is_sublcd(struct sh_mobile_lcdc_chan *chan)
{
	return chan->cfg->chan == LCDC_CHAN_SUBLCD;
}