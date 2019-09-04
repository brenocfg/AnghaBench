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
struct TYPE_2__ {scalar_t__ rev; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_DACK_TIMER ; 
 int /*<<< orphan*/  A_TP_FINWAIT2_TIMER ; 
 int /*<<< orphan*/  A_TP_INIT_SRTT ; 
 int /*<<< orphan*/  A_TP_KEEP_IDLE ; 
 int /*<<< orphan*/  A_TP_KEEP_INTVL ; 
 int /*<<< orphan*/  A_TP_MSL ; 
 int /*<<< orphan*/  A_TP_PERS_MAX ; 
 int /*<<< orphan*/  A_TP_PERS_MIN ; 
 int /*<<< orphan*/  A_TP_RXT_MAX ; 
 int /*<<< orphan*/  A_TP_RXT_MIN ; 
 int /*<<< orphan*/  A_TP_SHIFT_CNT ; 
 int /*<<< orphan*/  A_TP_TCP_BACKOFF_REG0 ; 
 int /*<<< orphan*/  A_TP_TCP_BACKOFF_REG1 ; 
 int /*<<< orphan*/  A_TP_TCP_BACKOFF_REG2 ; 
 int /*<<< orphan*/  A_TP_TCP_BACKOFF_REG3 ; 
 int /*<<< orphan*/  A_TP_TIMER_RESOLUTION ; 
 int TP_DACK_TIMER ; 
 int TP_RTO_MIN ; 
 int TP_TMR_RES ; 
 int V_DELAYEDACKRESOLUTION (unsigned int) ; 
 int V_KEEPALIVEMAX (int) ; 
 int V_PERSHIFTBACKOFFMAX (int) ; 
 int V_PERSHIFTMAX (int) ; 
 int V_RXTSHIFTMAXR1 (int) ; 
 int V_RXTSHIFTMAXR2 (int) ; 
 int V_SYNSHIFTMAX (int) ; 
 int V_TIMERRESOLUTION (unsigned int) ; 
 int V_TIMESTAMPRESOLUTION (unsigned int) ; 
 int fls (unsigned int) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tp_set_timers(struct adapter *adap, unsigned int core_clk)
{
	unsigned int tre = fls(core_clk / (1000000 / TP_TMR_RES)) - 1;
	unsigned int dack_re = fls(core_clk / 5000) - 1;	/* 200us */
	unsigned int tstamp_re = fls(core_clk / 1000);	/* 1ms, at least */
	unsigned int tps = core_clk >> tre;

	t3_write_reg(adap, A_TP_TIMER_RESOLUTION, V_TIMERRESOLUTION(tre) |
		     V_DELAYEDACKRESOLUTION(dack_re) |
		     V_TIMESTAMPRESOLUTION(tstamp_re));
	t3_write_reg(adap, A_TP_DACK_TIMER,
		     (core_clk >> dack_re) / (1000 / TP_DACK_TIMER));
	t3_write_reg(adap, A_TP_TCP_BACKOFF_REG0, 0x3020100);
	t3_write_reg(adap, A_TP_TCP_BACKOFF_REG1, 0x7060504);
	t3_write_reg(adap, A_TP_TCP_BACKOFF_REG2, 0xb0a0908);
	t3_write_reg(adap, A_TP_TCP_BACKOFF_REG3, 0xf0e0d0c);
	t3_write_reg(adap, A_TP_SHIFT_CNT, V_SYNSHIFTMAX(6) |
		     V_RXTSHIFTMAXR1(4) | V_RXTSHIFTMAXR2(15) |
		     V_PERSHIFTBACKOFFMAX(8) | V_PERSHIFTMAX(8) |
		     V_KEEPALIVEMAX(9));

#define SECONDS * tps

	t3_write_reg(adap, A_TP_MSL, adap->params.rev > 0 ? 0 : 2 SECONDS);
	t3_write_reg(adap, A_TP_RXT_MIN, tps / (1000 / TP_RTO_MIN));
	t3_write_reg(adap, A_TP_RXT_MAX, 64 SECONDS);
	t3_write_reg(adap, A_TP_PERS_MIN, 5 SECONDS);
	t3_write_reg(adap, A_TP_PERS_MAX, 64 SECONDS);
	t3_write_reg(adap, A_TP_KEEP_IDLE, 7200 SECONDS);
	t3_write_reg(adap, A_TP_KEEP_INTVL, 75 SECONDS);
	t3_write_reg(adap, A_TP_INIT_SRTT, 3 SECONDS);
	t3_write_reg(adap, A_TP_FINWAIT2_TIMER, 600 SECONDS);

#undef SECONDS
}