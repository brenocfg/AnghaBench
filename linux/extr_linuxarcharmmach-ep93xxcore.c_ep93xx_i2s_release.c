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

/* Variables and functions */
 int /*<<< orphan*/  EP93XX_SYSCON_DEVCFG_I2S_MASK ; 
 int /*<<< orphan*/  ep93xx_devcfg_clear_bits (int /*<<< orphan*/ ) ; 

void ep93xx_i2s_release(void)
{
	ep93xx_devcfg_clear_bits(EP93XX_SYSCON_DEVCFG_I2S_MASK);
}