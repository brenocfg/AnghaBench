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
typedef  unsigned int u32 ;

/* Variables and functions */
 scalar_t__ sirfsoc_rtc_iobrg_readl (unsigned int) ; 

__attribute__((used)) static int regmap_iobg_regread(void *context, unsigned int reg,
				  unsigned int *val)
{
	*val = (u32)sirfsoc_rtc_iobrg_readl(reg);
	return 0;
}