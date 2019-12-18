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
struct TYPE_2__ {int /*<<< orphan*/  hw_state; scalar_t__ mac_ring_is_up; } ;
struct s_smc {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B0_CTRL ; 
 int /*<<< orphan*/  B0_LED ; 
 int CTRL_HPI_SET ; 
 int CTRL_RST_CLR ; 
 int CTRL_RST_SET ; 
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_MDREG1 ; 
 int /*<<< orphan*/  FM_MINIT ; 
 int LED_GA_OFF ; 
 int LED_GB_OFF ; 
 int LED_MY_OFF ; 
 int /*<<< orphan*/  MS2BCLK (int) ; 
 int /*<<< orphan*/  STOPPED ; 
 int /*<<< orphan*/  hwt_quick_read (struct s_smc*) ; 
 int /*<<< orphan*/  hwt_wait_time (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smt_stop_watchdog (struct s_smc*) ; 

void card_stop(struct s_smc *smc)
{
	smt_stop_watchdog(smc) ;
	smc->hw.mac_ring_is_up = 0 ;		/* ring down */

#ifdef	PCI
	/*
	 * make sure no transfer activity is pending
	 */
	outpw(FM_A(FM_MDREG1),FM_MINIT) ;
	outp(ADDR(B0_CTRL), CTRL_HPI_SET) ;
	hwt_wait_time(smc,hwt_quick_read(smc),MS2BCLK(10)) ;
	/*
	 * now reset everything
	 */
	outp(ADDR(B0_CTRL),CTRL_RST_SET) ;	/* reset for all chips */
	outp(ADDR(B0_CTRL),CTRL_RST_CLR) ;	/* reset for all chips */
	outp(ADDR(B0_LED),LED_GA_OFF|LED_MY_OFF|LED_GB_OFF) ; /* all LEDs off */
	smc->hw.hw_state = STOPPED ;
#endif
}