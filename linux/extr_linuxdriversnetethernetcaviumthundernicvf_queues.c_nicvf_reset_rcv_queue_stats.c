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
struct TYPE_2__ {int rx_stat_mask; int tx_stat_mask; int rq_stat_mask; int sq_stat_mask; int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ reset_stat; } ;
struct nicvf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_MBOX_MSG_RESET_STAT_COUNTER ; 
 int /*<<< orphan*/  nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 

__attribute__((used)) static void nicvf_reset_rcv_queue_stats(struct nicvf *nic)
{
	union nic_mbx mbx = {};

	/* Reset all RQ/SQ and VF stats */
	mbx.reset_stat.msg = NIC_MBOX_MSG_RESET_STAT_COUNTER;
	mbx.reset_stat.rx_stat_mask = 0x3FFF;
	mbx.reset_stat.tx_stat_mask = 0x1F;
	mbx.reset_stat.rq_stat_mask = 0xFFFF;
	mbx.reset_stat.sq_stat_mask = 0xFFFF;
	nicvf_send_msg_to_pf(nic, &mbx);
}