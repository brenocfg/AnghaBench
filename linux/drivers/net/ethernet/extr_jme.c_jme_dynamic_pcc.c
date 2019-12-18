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
struct dynpcc_info {scalar_t__ last_bytes; scalar_t__ last_pkts; scalar_t__ intr_cnt; scalar_t__ attempt; scalar_t__ cur; int cnt; } ;
struct jme_adapter {int /*<<< orphan*/  rxclean_task; struct dynpcc_info dpi; } ;
struct TYPE_2__ {scalar_t__ rx_bytes; scalar_t__ rx_packets; } ;

/* Variables and functions */
 TYPE_1__ NET_STAT (struct jme_adapter*) ; 
 scalar_t__ PCC_INTR_THRESHOLD ; 
 int /*<<< orphan*/  PCC_P1 ; 
 int /*<<< orphan*/  PCC_P2 ; 
 scalar_t__ PCC_P2_THRESHOLD ; 
 int /*<<< orphan*/  PCC_P3 ; 
 scalar_t__ PCC_P3_THRESHOLD ; 
 int /*<<< orphan*/  jme_attempt_pcc (struct dynpcc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jme_set_rx_pcc (struct jme_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
jme_dynamic_pcc(struct jme_adapter *jme)
{
	register struct dynpcc_info *dpi = &(jme->dpi);

	if ((NET_STAT(jme).rx_bytes - dpi->last_bytes) > PCC_P3_THRESHOLD)
		jme_attempt_pcc(dpi, PCC_P3);
	else if ((NET_STAT(jme).rx_packets - dpi->last_pkts) > PCC_P2_THRESHOLD ||
		 dpi->intr_cnt > PCC_INTR_THRESHOLD)
		jme_attempt_pcc(dpi, PCC_P2);
	else
		jme_attempt_pcc(dpi, PCC_P1);

	if (unlikely(dpi->attempt != dpi->cur && dpi->cnt > 5)) {
		if (dpi->attempt < dpi->cur)
			tasklet_schedule(&jme->rxclean_task);
		jme_set_rx_pcc(jme, dpi->attempt);
		dpi->cur = dpi->attempt;
		dpi->cnt = 0;
	}
}