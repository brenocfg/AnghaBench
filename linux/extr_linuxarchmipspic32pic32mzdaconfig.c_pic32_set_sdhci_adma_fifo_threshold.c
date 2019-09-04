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
 int /*<<< orphan*/  PIC32_CFGCON2 ; 
 int pic32_conf_modify_atomic (int /*<<< orphan*/ ,int,int) ; 

int pic32_set_sdhci_adma_fifo_threshold(u32 rthrsh, u32 wthrsh)
{
	u32 clr, set;

	clr = (0x3ff << 4) | (0x3ff << 16);
	set = (rthrsh << 4) | (wthrsh << 16);
	return pic32_conf_modify_atomic(PIC32_CFGCON2, clr, set);
}