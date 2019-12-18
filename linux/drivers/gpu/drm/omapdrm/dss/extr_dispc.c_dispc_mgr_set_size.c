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
typedef  scalar_t__ u16 ;
struct dispc_device {TYPE_1__* feat; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_2__ {int /*<<< orphan*/  mgr_width_start; int /*<<< orphan*/  mgr_height_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_SIZE_MGR (int) ; 
 int FLD_VAL (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dispc_write_reg (struct dispc_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dispc_mgr_set_size(struct dispc_device *dispc,
			       enum omap_channel channel, u16 width, u16 height)
{
	u32 val;

	val = FLD_VAL(height - 1, dispc->feat->mgr_height_start, 16) |
		FLD_VAL(width - 1, dispc->feat->mgr_width_start, 0);

	dispc_write_reg(dispc, DISPC_SIZE_MGR(channel), val);
}