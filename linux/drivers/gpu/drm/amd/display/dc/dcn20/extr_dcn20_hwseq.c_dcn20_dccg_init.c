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
struct dce_hwseq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPCLK_FREQ_CHANGE_CNTL ; 
 int /*<<< orphan*/  MICROSECOND_TIME_BASE_DIV ; 
 int /*<<< orphan*/  MILLISECOND_TIME_BASE_DIV ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 

void dcn20_dccg_init(struct dce_hwseq *hws)
{
	/*
	 * set MICROSECOND_TIME_BASE_DIV
	 * 100Mhz refclk -> 0x120264
	 * 27Mhz refclk -> 0x12021b
	 * 48Mhz refclk -> 0x120230
	 *
	 */
	REG_WRITE(MICROSECOND_TIME_BASE_DIV, 0x120264);

	/*
	 * set MILLISECOND_TIME_BASE_DIV
	 * 100Mhz refclk -> 0x1186a0
	 * 27Mhz refclk -> 0x106978
	 * 48Mhz refclk -> 0x10bb80
	 *
	 */
	REG_WRITE(MILLISECOND_TIME_BASE_DIV, 0x1186a0);

	/* This value is dependent on the hardware pipeline delay so set once per SOC */
	REG_WRITE(DISPCLK_FREQ_CHANGE_CNTL, 0x801003c);
}