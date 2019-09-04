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
 int HDMI_8x60_PHY_REG0_DESER_DEL_CTRL__MASK ; 
 int HDMI_8x60_PHY_REG0_DESER_DEL_CTRL__SHIFT ; 

__attribute__((used)) static inline uint32_t HDMI_8x60_PHY_REG0_DESER_DEL_CTRL(uint32_t val)
{
	return ((val) << HDMI_8x60_PHY_REG0_DESER_DEL_CTRL__SHIFT) & HDMI_8x60_PHY_REG0_DESER_DEL_CTRL__MASK;
}