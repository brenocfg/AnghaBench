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

/* Variables and functions */
 int DSI_20nm_PHY_TIMING_CTRL_8_HS_RQST__MASK ; 
 int DSI_20nm_PHY_TIMING_CTRL_8_HS_RQST__SHIFT ; 

__attribute__((used)) static inline uint32_t DSI_20nm_PHY_TIMING_CTRL_8_HS_RQST(uint32_t val)
{
	return ((val) << DSI_20nm_PHY_TIMING_CTRL_8_HS_RQST__SHIFT) & DSI_20nm_PHY_TIMING_CTRL_8_HS_RQST__MASK;
}