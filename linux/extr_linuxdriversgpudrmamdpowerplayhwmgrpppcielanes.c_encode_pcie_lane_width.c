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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/ * pp_r600_encode_lanes ; 

uint8_t encode_pcie_lane_width(uint32_t num_lanes)
{
	return pp_r600_encode_lanes[num_lanes];
}