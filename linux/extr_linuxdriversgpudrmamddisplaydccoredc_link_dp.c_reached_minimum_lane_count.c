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
typedef  enum dc_lane_count { ____Placeholder_dc_lane_count } dc_lane_count ;

/* Variables and functions */
 int LANE_COUNT_ONE ; 

__attribute__((used)) static inline bool reached_minimum_lane_count(enum dc_lane_count lane_count)
{
	return lane_count <= LANE_COUNT_ONE;
}