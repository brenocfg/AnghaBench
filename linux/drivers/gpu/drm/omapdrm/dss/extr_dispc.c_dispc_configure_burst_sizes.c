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
struct dispc_device {TYPE_1__* feat; } ;
struct TYPE_2__ {scalar_t__ has_writeback; } ;

/* Variables and functions */
 int BURST_SIZE_X8 ; 
 int OMAP_DSS_WB ; 
 int dispc_get_num_ovls (struct dispc_device*) ; 
 int /*<<< orphan*/  dispc_ovl_set_burst_size (struct dispc_device*,int,int const) ; 

__attribute__((used)) static void dispc_configure_burst_sizes(struct dispc_device *dispc)
{
	int i;
	const int burst_size = BURST_SIZE_X8;

	/* Configure burst size always to maximum size */
	for (i = 0; i < dispc_get_num_ovls(dispc); ++i)
		dispc_ovl_set_burst_size(dispc, i, burst_size);
	if (dispc->feat->has_writeback)
		dispc_ovl_set_burst_size(dispc, OMAP_DSS_WB, burst_size);
}