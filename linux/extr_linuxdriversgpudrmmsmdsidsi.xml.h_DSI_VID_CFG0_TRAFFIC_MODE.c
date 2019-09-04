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
typedef  int uint32_t ;
typedef  enum dsi_traffic_mode { ____Placeholder_dsi_traffic_mode } dsi_traffic_mode ;

/* Variables and functions */
 int DSI_VID_CFG0_TRAFFIC_MODE__MASK ; 
 int DSI_VID_CFG0_TRAFFIC_MODE__SHIFT ; 

__attribute__((used)) static inline uint32_t DSI_VID_CFG0_TRAFFIC_MODE(enum dsi_traffic_mode val)
{
	return ((val) << DSI_VID_CFG0_TRAFFIC_MODE__SHIFT) & DSI_VID_CFG0_TRAFFIC_MODE__MASK;
}