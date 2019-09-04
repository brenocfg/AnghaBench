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
 int DSI_14nm_PHY_LN_CFG0_PREPARE_DLY__MASK ; 
 int DSI_14nm_PHY_LN_CFG0_PREPARE_DLY__SHIFT ; 

__attribute__((used)) static inline uint32_t DSI_14nm_PHY_LN_CFG0_PREPARE_DLY(uint32_t val)
{
	return ((val) << DSI_14nm_PHY_LN_CFG0_PREPARE_DLY__SHIFT) & DSI_14nm_PHY_LN_CFG0_PREPARE_DLY__MASK;
}