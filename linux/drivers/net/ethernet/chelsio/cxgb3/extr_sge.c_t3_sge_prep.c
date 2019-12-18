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
struct skb_shared_info {int dummy; } ;
struct sge_params {struct qset_params* qset; scalar_t__ max_pkt_size; } ;
struct qset_params {int polling; int coalesce_usecs; int rspq_size; int fl_size; int jumbo_size; int* txq_size; scalar_t__ cong_thres; } ;
struct cpl_rx_data {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  reg_lock; } ;
struct TYPE_3__ {scalar_t__ rev; } ;
struct adapter {TYPE_2__ sge; TYPE_1__ params; } ;

/* Variables and functions */
 int SGE_QSETS ; 
 scalar_t__ SKB_DATA_ALIGN (int) ; 
 size_t TXQ_CTRL ; 
 size_t TXQ_ETH ; 
 size_t TXQ_OFLD ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void t3_sge_prep(struct adapter *adap, struct sge_params *p)
{
	int i;

	p->max_pkt_size = (16 * 1024) - sizeof(struct cpl_rx_data) -
	    SKB_DATA_ALIGN(sizeof(struct skb_shared_info));

	for (i = 0; i < SGE_QSETS; ++i) {
		struct qset_params *q = p->qset + i;

		q->polling = adap->params.rev > 0;
		q->coalesce_usecs = 5;
		q->rspq_size = 1024;
		q->fl_size = 1024;
 		q->jumbo_size = 512;
		q->txq_size[TXQ_ETH] = 1024;
		q->txq_size[TXQ_OFLD] = 1024;
		q->txq_size[TXQ_CTRL] = 256;
		q->cong_thres = 0;
	}

	spin_lock_init(&adap->sge.reg_lock);
}