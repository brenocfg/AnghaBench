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
struct lpc32xx_tsc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC32XX_TSC_FIFO ; 
 int /*<<< orphan*/  LPC32XX_TSC_STAT ; 
 int LPC32XX_TSC_STAT_FIFO_EMPTY ; 
 int tsc_readl (struct lpc32xx_tsc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpc32xx_fifo_clear(struct lpc32xx_tsc *tsc)
{
	while (!(tsc_readl(tsc, LPC32XX_TSC_STAT) &
			LPC32XX_TSC_STAT_FIFO_EMPTY))
		tsc_readl(tsc, LPC32XX_TSC_FIFO);
}