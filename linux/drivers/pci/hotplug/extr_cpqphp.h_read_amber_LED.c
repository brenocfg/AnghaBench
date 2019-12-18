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
struct controller {scalar_t__ hpc_reg; } ;

/* Variables and functions */
 scalar_t__ LED_CONTROL ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static inline int read_amber_LED(struct controller *ctrl, u8 slot)
{
	u32 led_control;

	led_control = readl(ctrl->hpc_reg + LED_CONTROL);
	led_control &= (0x01010000L << slot);

	return led_control ? 1 : 0;
}