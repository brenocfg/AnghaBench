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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ nchan; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 scalar_t__ NCHAN ; 
 int /*<<< orphan*/  OFDRATE0_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OFDRATE1_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OFDRATE2_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OFDRATE3_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TNLRATE0_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TNLRATE1_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TNLRATE2_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TNLRATE3_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TP_TX_ORATE_A ; 
 int /*<<< orphan*/  TP_TX_TRATE_A ; 
 int /*<<< orphan*/  chan_rate (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

void t4_get_chan_txrate(struct adapter *adap, u64 *nic_rate, u64 *ofld_rate)
{
	u32 v;

	v = t4_read_reg(adap, TP_TX_TRATE_A);
	nic_rate[0] = chan_rate(adap, TNLRATE0_G(v));
	nic_rate[1] = chan_rate(adap, TNLRATE1_G(v));
	if (adap->params.arch.nchan == NCHAN) {
		nic_rate[2] = chan_rate(adap, TNLRATE2_G(v));
		nic_rate[3] = chan_rate(adap, TNLRATE3_G(v));
	}

	v = t4_read_reg(adap, TP_TX_ORATE_A);
	ofld_rate[0] = chan_rate(adap, OFDRATE0_G(v));
	ofld_rate[1] = chan_rate(adap, OFDRATE1_G(v));
	if (adap->params.arch.nchan == NCHAN) {
		ofld_rate[2] = chan_rate(adap, OFDRATE2_G(v));
		ofld_rate[3] = chan_rate(adap, OFDRATE3_G(v));
	}
}