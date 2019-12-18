#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */

u8 r600_encode_pci_lane_width(u32 lanes)
{
	u8 encoded_lanes[] = { 0, 1, 2, 0, 3, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 6 };

	if (lanes > 16)
		return 0;

	return encoded_lanes[lanes];
}