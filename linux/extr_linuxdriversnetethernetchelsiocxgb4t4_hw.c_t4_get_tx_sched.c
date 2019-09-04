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
struct TYPE_3__ {int cclk; } ;
struct TYPE_4__ {TYPE_1__ vpd; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 unsigned int TP_TX_MOD_Q1_Q0_RATE_LIMIT_A ; 
 unsigned int TP_TX_MOD_Q1_Q0_TIMER_SEPARATOR_A ; 
 int core_ticks_per_usec (struct adapter*) ; 
 int /*<<< orphan*/  t4_tp_tm_pio_read (struct adapter*,unsigned int*,int,unsigned int,int) ; 

void t4_get_tx_sched(struct adapter *adap, unsigned int sched,
		     unsigned int *kbps, unsigned int *ipg, bool sleep_ok)
{
	unsigned int v, addr, bpt, cpt;

	if (kbps) {
		addr = TP_TX_MOD_Q1_Q0_RATE_LIMIT_A - sched / 2;
		t4_tp_tm_pio_read(adap, &v, 1, addr, sleep_ok);
		if (sched & 1)
			v >>= 16;
		bpt = (v >> 8) & 0xff;
		cpt = v & 0xff;
		if (!cpt) {
			*kbps = 0;	/* scheduler disabled */
		} else {
			v = (adap->params.vpd.cclk * 1000) / cpt; /* ticks/s */
			*kbps = (v * bpt) / 125;
		}
	}
	if (ipg) {
		addr = TP_TX_MOD_Q1_Q0_TIMER_SEPARATOR_A - sched / 2;
		t4_tp_tm_pio_read(adap, &v, 1, addr, sleep_ok);
		if (sched & 1)
			v >>= 16;
		v &= 0xffff;
		*ipg = (10000 * v) / core_ticks_per_usec(adap);
	}
}