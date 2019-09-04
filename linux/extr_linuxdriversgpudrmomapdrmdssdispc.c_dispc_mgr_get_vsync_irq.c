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
typedef  int /*<<< orphan*/  u32 ;
struct dispc_device {int dummy; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_2__ {int /*<<< orphan*/  vsync_irq; } ;

/* Variables and functions */
 TYPE_1__* mgr_desc ; 

__attribute__((used)) static u32 dispc_mgr_get_vsync_irq(struct dispc_device *dispc,
				   enum omap_channel channel)
{
	return mgr_desc[channel].vsync_irq;
}