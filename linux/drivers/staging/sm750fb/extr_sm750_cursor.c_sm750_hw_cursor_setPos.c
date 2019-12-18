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
 int /*<<< orphan*/  HWC_LOCATION ; 
 int HWC_LOCATION_X_MASK ; 
 int HWC_LOCATION_Y_MASK ; 
 int HWC_LOCATION_Y_SHIFT ; 
 int /*<<< orphan*/  poke32 (int /*<<< orphan*/ ,int) ; 

void sm750_hw_cursor_setPos(struct lynx_cursor *cursor, int x, int y)
{
	u32 reg;

	reg = ((y << HWC_LOCATION_Y_SHIFT) & HWC_LOCATION_Y_MASK) |
	       (x & HWC_LOCATION_X_MASK);
	poke32(HWC_LOCATION, reg);
}