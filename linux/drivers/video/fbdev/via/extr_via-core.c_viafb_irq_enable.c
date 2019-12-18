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

/* Variables and functions */
 int /*<<< orphan*/  VDE_INTERRUPT ; 
 int VDE_I_ENABLE ; 
 int viafb_enabled_ints ; 
 int /*<<< orphan*/  viafb_mmio_write (int /*<<< orphan*/ ,int) ; 

void viafb_irq_enable(u32 mask)
{
	viafb_enabled_ints |= mask;
	viafb_mmio_write(VDE_INTERRUPT, viafb_enabled_ints | VDE_I_ENABLE);
}