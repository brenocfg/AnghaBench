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
struct lynx_cursor {int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWC_ADDRESS ; 
 int HWC_ADDRESS_ADDRESS_MASK ; 
 int HWC_ADDRESS_ENABLE ; 
 int /*<<< orphan*/  poke32 (int /*<<< orphan*/ ,int) ; 

void sm750_hw_cursor_enable(struct lynx_cursor *cursor)
{
	u32 reg;

	reg = (cursor->offset & HWC_ADDRESS_ADDRESS_MASK) | HWC_ADDRESS_ENABLE;
	poke32(HWC_ADDRESS, reg);
}