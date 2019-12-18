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
typedef  int u32 ;
struct lynx_cursor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWC_COLOR_12 ; 
 int HWC_COLOR_12_1_RGB565_MASK ; 
 int HWC_COLOR_12_2_RGB565_MASK ; 
 int HWC_COLOR_12_2_RGB565_SHIFT ; 
 int /*<<< orphan*/  HWC_COLOR_3 ; 
 int /*<<< orphan*/  poke32 (int /*<<< orphan*/ ,int) ; 

void sm750_hw_cursor_setColor(struct lynx_cursor *cursor, u32 fg, u32 bg)
{
	u32 reg = (fg << HWC_COLOR_12_2_RGB565_SHIFT) &
		HWC_COLOR_12_2_RGB565_MASK;

	poke32(HWC_COLOR_12, reg | (bg & HWC_COLOR_12_1_RGB565_MASK));
	poke32(HWC_COLOR_3, 0xffe0);
}