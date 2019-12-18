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
typedef  int u64 ;
struct sk_buff {int dummy; } ;
struct bnx2x {int /*<<< orphan*/  timecounter; } ;
struct TYPE_2__ {int /*<<< orphan*/  hwtstamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_PTP ; 
 int BP_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  NIG_REG_P0_LLH_PTP_HOST_BUF_SEQID ; 
 int /*<<< orphan*/  NIG_REG_P0_LLH_PTP_HOST_BUF_TS_LSB ; 
 int /*<<< orphan*/  NIG_REG_P0_LLH_PTP_HOST_BUF_TS_MSB ; 
 int /*<<< orphan*/  NIG_REG_P1_LLH_PTP_HOST_BUF_SEQID ; 
 int /*<<< orphan*/  NIG_REG_P1_LLH_PTP_HOST_BUF_TS_LSB ; 
 int /*<<< orphan*/  NIG_REG_P1_LLH_PTP_HOST_BUF_TS_MSB ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ns_to_ktime (int) ; 
 TYPE_1__* skb_hwtstamps (struct sk_buff*) ; 
 int timecounter_cyc2time (int /*<<< orphan*/ *,int) ; 

void bnx2x_set_rx_ts(struct bnx2x *bp, struct sk_buff *skb)
{
	int port = BP_PORT(bp);
	u64 timestamp, ns;

	timestamp = REG_RD(bp, port ? NIG_REG_P1_LLH_PTP_HOST_BUF_TS_MSB :
			    NIG_REG_P0_LLH_PTP_HOST_BUF_TS_MSB);
	timestamp <<= 32;
	timestamp |= REG_RD(bp, port ? NIG_REG_P1_LLH_PTP_HOST_BUF_TS_LSB :
			    NIG_REG_P0_LLH_PTP_HOST_BUF_TS_LSB);

	/* Reset timestamp register to allow new timestamp */
	REG_WR(bp, port ? NIG_REG_P1_LLH_PTP_HOST_BUF_SEQID :
	       NIG_REG_P0_LLH_PTP_HOST_BUF_SEQID, 0x10000);

	ns = timecounter_cyc2time(&bp->timecounter, timestamp);

	skb_hwtstamps(skb)->hwtstamp = ns_to_ktime(ns);

	DP(BNX2X_MSG_PTP, "Rx timestamp, timestamp cycles = %llu, ns = %llu\n",
	   timestamp, ns);
}