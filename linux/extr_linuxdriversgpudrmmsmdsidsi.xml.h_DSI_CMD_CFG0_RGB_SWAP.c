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
typedef  enum dsi_rgb_swap { ____Placeholder_dsi_rgb_swap } dsi_rgb_swap ;

/* Variables and functions */
 int DSI_CMD_CFG0_RGB_SWAP__MASK ; 
 int DSI_CMD_CFG0_RGB_SWAP__SHIFT ; 

__attribute__((used)) static inline uint32_t DSI_CMD_CFG0_RGB_SWAP(enum dsi_rgb_swap val)
{
	return ((val) << DSI_CMD_CFG0_RGB_SWAP__SHIFT) & DSI_CMD_CFG0_RGB_SWAP__MASK;
}