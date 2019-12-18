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
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;
struct TYPE_4__ {int* fifo_assignment; scalar_t__* fifo_size; TYPE_1__* feat; } ;
struct TYPE_3__ {int num_fifos; } ;

/* Variables and functions */
 TYPE_2__ dispc ; 

__attribute__((used)) static u32 dispc_ovl_get_fifo_size(enum omap_plane plane)
{
	int fifo;
	u32 size = 0;

	for (fifo = 0; fifo < dispc.feat->num_fifos; ++fifo) {
		if (dispc.fifo_assignment[fifo] == plane)
			size += dispc.fifo_size[fifo];
	}

	return size;
}