#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int dummy; } ;
struct cudbg_clk_info {int cclk_ps; int res; int tre; int dack_re; int dack_timer; int retransmit_min; int retransmit_max; int persist_timer_min; int persist_timer_max; int keepalive_idle_timer; int keepalive_interval; int initial_srtt; int finwait2_timer; } ;
struct cudbg_buffer {scalar_t__ data; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int cclk; } ;
struct TYPE_4__ {TYPE_1__ vpd; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 int CUDBG_STATUS_CCLK_NOT_DEFINED ; 
 int DELAYEDACKRESOLUTION_G (int) ; 
 int INITSRTT_G (int) ; 
 int TIMERRESOLUTION_G (int) ; 
 int /*<<< orphan*/  TP_DACK_TIMER_A ; 
 int /*<<< orphan*/  TP_FINWAIT2_TIMER_A ; 
 int /*<<< orphan*/  TP_INIT_SRTT_A ; 
 int /*<<< orphan*/  TP_KEEP_IDLE_A ; 
 int /*<<< orphan*/  TP_KEEP_INTVL_A ; 
 int /*<<< orphan*/  TP_PERS_MAX_A ; 
 int /*<<< orphan*/  TP_PERS_MIN_A ; 
 int /*<<< orphan*/  TP_RXT_MAX_A ; 
 int /*<<< orphan*/  TP_RXT_MIN_A ; 
 int /*<<< orphan*/  TP_TIMER_RESOLUTION_A ; 
 int cudbg_get_buff (struct cudbg_init*,struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 int cudbg_write_and_release_buff (struct cudbg_init*,struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

int cudbg_collect_clk_info(struct cudbg_init *pdbg_init,
			   struct cudbg_buffer *dbg_buff,
			   struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_buffer temp_buff = { 0 };
	struct cudbg_clk_info *clk_info_buff;
	u64 tp_tick_us;
	int rc;

	if (!padap->params.vpd.cclk)
		return CUDBG_STATUS_CCLK_NOT_DEFINED;

	rc = cudbg_get_buff(pdbg_init, dbg_buff, sizeof(struct cudbg_clk_info),
			    &temp_buff);
	if (rc)
		return rc;

	clk_info_buff = (struct cudbg_clk_info *)temp_buff.data;
	clk_info_buff->cclk_ps = 1000000000 / padap->params.vpd.cclk; /* psec */
	clk_info_buff->res = t4_read_reg(padap, TP_TIMER_RESOLUTION_A);
	clk_info_buff->tre = TIMERRESOLUTION_G(clk_info_buff->res);
	clk_info_buff->dack_re = DELAYEDACKRESOLUTION_G(clk_info_buff->res);
	tp_tick_us = (clk_info_buff->cclk_ps << clk_info_buff->tre) / 1000000;

	clk_info_buff->dack_timer =
		(clk_info_buff->cclk_ps << clk_info_buff->dack_re) / 1000000 *
		t4_read_reg(padap, TP_DACK_TIMER_A);
	clk_info_buff->retransmit_min =
		tp_tick_us * t4_read_reg(padap, TP_RXT_MIN_A);
	clk_info_buff->retransmit_max =
		tp_tick_us * t4_read_reg(padap, TP_RXT_MAX_A);
	clk_info_buff->persist_timer_min =
		tp_tick_us * t4_read_reg(padap, TP_PERS_MIN_A);
	clk_info_buff->persist_timer_max =
		tp_tick_us * t4_read_reg(padap, TP_PERS_MAX_A);
	clk_info_buff->keepalive_idle_timer =
		tp_tick_us * t4_read_reg(padap, TP_KEEP_IDLE_A);
	clk_info_buff->keepalive_interval =
		tp_tick_us * t4_read_reg(padap, TP_KEEP_INTVL_A);
	clk_info_buff->initial_srtt =
		tp_tick_us * INITSRTT_G(t4_read_reg(padap, TP_INIT_SRTT_A));
	clk_info_buff->finwait2_timer =
		tp_tick_us * t4_read_reg(padap, TP_FINWAIT2_TIMER_A);

	return cudbg_write_and_release_buff(pdbg_init, &temp_buff, dbg_buff);
}