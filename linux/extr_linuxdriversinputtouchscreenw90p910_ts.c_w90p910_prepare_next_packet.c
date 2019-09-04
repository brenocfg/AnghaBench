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
struct w90p910_ts {int /*<<< orphan*/  state; int /*<<< orphan*/  ts_reg; } ;

/* Variables and functions */
 unsigned long ADC_CONV ; 
 unsigned long ADC_INT ; 
 unsigned long ADC_INT_EN ; 
 unsigned long ADC_SEMIAUTO ; 
 unsigned long ADC_WAITTRIG ; 
 int /*<<< orphan*/  TS_WAIT_NEW_PACKET ; 
 unsigned long WT_INT_EN ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void w90p910_prepare_next_packet(struct w90p910_ts *w90p910_ts)
{
	unsigned long ctlreg;

	ctlreg = __raw_readl(w90p910_ts->ts_reg);
	ctlreg &= ~(ADC_INT | ADC_INT_EN | ADC_SEMIAUTO | ADC_CONV);
	ctlreg |= ADC_WAITTRIG | WT_INT_EN;
	__raw_writel(ctlreg, w90p910_ts->ts_reg);

	w90p910_ts->state = TS_WAIT_NEW_PACKET;
}