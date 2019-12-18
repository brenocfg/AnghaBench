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
typedef  unsigned long long u32 ;
struct seq_file {struct adapter* private; } ;
struct TYPE_3__ {int cclk; } ;
struct TYPE_4__ {TYPE_1__ vpd; } ;
struct adapter {TYPE_2__ params; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 unsigned int DELAYEDACKRESOLUTION_G (unsigned long long) ; 
 unsigned long long INITSRTT_G (unsigned long long) ; 
 unsigned int TIMERRESOLUTION_G (unsigned long long) ; 
 unsigned int TIMESTAMPRESOLUTION_G (unsigned long long) ; 
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
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long long) ; 
 unsigned long long t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 unsigned long long unit_conv (char*,int,unsigned int,int) ; 

__attribute__((used)) static int clk_show(struct seq_file *seq, void *v)
{
	char buf[32];
	struct adapter *adap = seq->private;
	unsigned int cclk_ps = 1000000000 / adap->params.vpd.cclk;  /* in ps */
	u32 res = t4_read_reg(adap, TP_TIMER_RESOLUTION_A);
	unsigned int tre = TIMERRESOLUTION_G(res);
	unsigned int dack_re = DELAYEDACKRESOLUTION_G(res);
	unsigned long long tp_tick_us = (cclk_ps << tre) / 1000000; /* in us */

	seq_printf(seq, "Core clock period: %s ns\n",
		   unit_conv(buf, sizeof(buf), cclk_ps, 1000));
	seq_printf(seq, "TP timer tick: %s us\n",
		   unit_conv(buf, sizeof(buf), (cclk_ps << tre), 1000000));
	seq_printf(seq, "TCP timestamp tick: %s us\n",
		   unit_conv(buf, sizeof(buf),
			     (cclk_ps << TIMESTAMPRESOLUTION_G(res)), 1000000));
	seq_printf(seq, "DACK tick: %s us\n",
		   unit_conv(buf, sizeof(buf), (cclk_ps << dack_re), 1000000));
	seq_printf(seq, "DACK timer: %u us\n",
		   ((cclk_ps << dack_re) / 1000000) *
		   t4_read_reg(adap, TP_DACK_TIMER_A));
	seq_printf(seq, "Retransmit min: %llu us\n",
		   tp_tick_us * t4_read_reg(adap, TP_RXT_MIN_A));
	seq_printf(seq, "Retransmit max: %llu us\n",
		   tp_tick_us * t4_read_reg(adap, TP_RXT_MAX_A));
	seq_printf(seq, "Persist timer min: %llu us\n",
		   tp_tick_us * t4_read_reg(adap, TP_PERS_MIN_A));
	seq_printf(seq, "Persist timer max: %llu us\n",
		   tp_tick_us * t4_read_reg(adap, TP_PERS_MAX_A));
	seq_printf(seq, "Keepalive idle timer: %llu us\n",
		   tp_tick_us * t4_read_reg(adap, TP_KEEP_IDLE_A));
	seq_printf(seq, "Keepalive interval: %llu us\n",
		   tp_tick_us * t4_read_reg(adap, TP_KEEP_INTVL_A));
	seq_printf(seq, "Initial SRTT: %llu us\n",
		   tp_tick_us * INITSRTT_G(t4_read_reg(adap, TP_INIT_SRTT_A)));
	seq_printf(seq, "FINWAIT2 timer: %llu us\n",
		   tp_tick_us * t4_read_reg(adap, TP_FINWAIT2_TIMER_A));

	return 0;
}