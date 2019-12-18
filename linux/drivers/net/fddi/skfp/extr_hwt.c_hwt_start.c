#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
typedef  scalar_t__ u_long ;
struct TYPE_2__ {long t_stop; int /*<<< orphan*/  timer_activ; scalar_t__ t_start; } ;
struct s_smc {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B2_TI_CRTL ; 
 int /*<<< orphan*/  B2_TI_INI ; 
 scalar_t__ HWT_MAX ; 
 int /*<<< orphan*/  TIM_START ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  outpd (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hwt_start(struct s_smc *smc, u_long time)
{
	u_short	cnt ;

	if (time > HWT_MAX)
		time = HWT_MAX ;

	smc->hw.t_start = time ;
	smc->hw.t_stop = 0L ;

	cnt = (u_short)time ;
	/*
	 * if time < 16 us
	 *	time = 16 us
	 */
	if (!cnt)
		cnt++ ;

	outpd(ADDR(B2_TI_INI), (u_long) cnt * 200) ;	/* Load timer value. */
	outpw(ADDR(B2_TI_CRTL), TIM_START) ;		/* Start timer. */

	smc->hw.timer_activ = TRUE ;
}