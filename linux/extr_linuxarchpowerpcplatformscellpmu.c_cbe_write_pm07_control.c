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
typedef  size_t u32 ;

/* Variables and functions */
 size_t NR_CTRS ; 
 int /*<<< orphan*/  WRITE_WO_MMIO (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * pm07_control ; 

void cbe_write_pm07_control(u32 cpu, u32 ctr, u32 val)
{
	if (ctr < NR_CTRS)
		WRITE_WO_MMIO(pm07_control[ctr], val);
}