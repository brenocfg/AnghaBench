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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  LPC32XX_CLKPWR_DEVID (int) ; 
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 

void lpc32xx_get_uid(u32 devid[4])
{
	int i;

	for (i = 0; i < 4; i++)
		devid[i] = __raw_readl(LPC32XX_CLKPWR_DEVID(i << 2));
}