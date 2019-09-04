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
typedef  int /*<<< orphan*/  u32 ;
struct dispc_device {TYPE_1__* feat; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_4__ {int /*<<< orphan*/  framedone_irq; } ;
struct TYPE_3__ {scalar_t__ no_framedone_tv; } ;

/* Variables and functions */
 int OMAP_DSS_CHANNEL_DIGIT ; 
 TYPE_2__* mgr_desc ; 

__attribute__((used)) static u32 dispc_mgr_get_framedone_irq(struct dispc_device *dispc,
				       enum omap_channel channel)
{
	if (channel == OMAP_DSS_CHANNEL_DIGIT && dispc->feat->no_framedone_tv)
		return 0;

	return mgr_desc[channel].framedone_irq;
}