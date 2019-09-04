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
struct tp_rdma_stats {int /*<<< orphan*/  rqe_dfr_pkt; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TP_MIB_RQE_DFR_PKT_A ; 
 int /*<<< orphan*/  t4_tp_mib_read (struct adapter*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

void t4_tp_get_rdma_stats(struct adapter *adap, struct tp_rdma_stats *st,
			  bool sleep_ok)
{
	t4_tp_mib_read(adap, &st->rqe_dfr_pkt, 2, TP_MIB_RQE_DFR_PKT_A,
		       sleep_ok);
}