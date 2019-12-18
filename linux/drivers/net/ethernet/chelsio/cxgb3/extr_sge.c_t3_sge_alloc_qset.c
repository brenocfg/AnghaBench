#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tx_sw_desc {int dummy; } ;
struct tx_desc {int dummy; } ;
struct skb_shared_info {int dummy; } ;
struct TYPE_7__ {int gen; int size; int /*<<< orphan*/  holdoff_tmr; int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  lock; void* desc; } ;
struct sge_qset {TYPE_3__ rspq; TYPE_4__* fl; struct netdev_queue* tx_q; struct net_device* netdev; struct adapter* adap; TYPE_1__* txq; int /*<<< orphan*/  rx_reclaim_timer; int /*<<< orphan*/  tx_reclaim_timer; } ;
struct rx_sw_desc {int dummy; } ;
struct rx_desc {int dummy; } ;
struct rsp_desc {int dummy; } ;
struct qset_params {int fl_size; int jumbo_size; int rspq_size; int* txq_size; int /*<<< orphan*/  cong_thres; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct cpl_rx_pkt {int dummy; } ;
struct cpl_rx_data {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  reg_lock; struct sge_qset* qs; } ;
struct adapter {TYPE_2__ sge; int /*<<< orphan*/  pdev; } ;
struct TYPE_8__ {int gen; int size; int buf_size; int use_pages; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  alloc_size; int /*<<< orphan*/  order; void* desc; int /*<<< orphan*/  sdesc; } ;
struct TYPE_5__ {int gen; int size; int stop_thres; int /*<<< orphan*/  token; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  qresume_tsk; int /*<<< orphan*/  sendq; int /*<<< orphan*/  lock; void* desc; int /*<<< orphan*/  sdesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_GTS ; 
 int /*<<< orphan*/  CH_ALERT (struct adapter*,char*) ; 
 int /*<<< orphan*/  CH_WARN (struct adapter*,char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FL0_PG_ALLOC_SIZE ; 
 scalar_t__ FL0_PG_CHUNK_SIZE ; 
 int /*<<< orphan*/  FL0_PG_ORDER ; 
 int /*<<< orphan*/  FL1_PG_ALLOC_SIZE ; 
 scalar_t__ FL1_PG_CHUNK_SIZE ; 
 int /*<<< orphan*/  FL1_PG_ORDER ; 
 int GFP_KERNEL ; 
 int MAX_FRAME_SIZE ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  SGE_CNTXT_CTRL ; 
 int /*<<< orphan*/  SGE_CNTXT_ETH ; 
 int /*<<< orphan*/  SGE_CNTXT_OFLD ; 
 int SGE_PG_RSVD ; 
 int SGE_RXQ_PER_SET ; 
 int SGE_RX_SM_BUF_SIZE ; 
 int SKB_DATA_ALIGN (int) ; 
 int TXQ_CTRL ; 
 size_t TXQ_ETH ; 
 size_t TXQ_OFLD ; 
 int /*<<< orphan*/  USE_GTS ; 
 int V_NEWTIMER (int /*<<< orphan*/ ) ; 
 int V_RSPQ (int /*<<< orphan*/ ) ; 
 int __GFP_COMP ; 
 void* alloc_ring (int /*<<< orphan*/ ,int,int,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int flits_to_desc (scalar_t__) ; 
 int /*<<< orphan*/  init_qset_cntxt (struct sge_qset*,unsigned int) ; 
 scalar_t__ is_offload (struct adapter*) ; 
 int refill_fl (struct adapter*,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  refill_rspq (struct adapter*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  restart_ctrlq ; 
 int /*<<< orphan*/  restart_offloadq ; 
 int /*<<< orphan*/  sge_timer_rx ; 
 int /*<<< orphan*/  sge_timer_tx ; 
 scalar_t__ sgl_len (scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_free_qset (struct adapter*,struct sge_qset*) ; 
 int t3_sge_init_ecntxt (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int t3_sge_init_flcntxt (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int t3_sge_init_rspcntxt (struct adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_update_qset_coalesce (struct sge_qset*,struct qset_params const*) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int t3_sge_alloc_qset(struct adapter *adapter, unsigned int id, int nports,
		      int irq_vec_idx, const struct qset_params *p,
		      int ntxq, struct net_device *dev,
		      struct netdev_queue *netdevq)
{
	int i, avail, ret = -ENOMEM;
	struct sge_qset *q = &adapter->sge.qs[id];

	init_qset_cntxt(q, id);
	timer_setup(&q->tx_reclaim_timer, sge_timer_tx, 0);
	timer_setup(&q->rx_reclaim_timer, sge_timer_rx, 0);

	q->fl[0].desc = alloc_ring(adapter->pdev, p->fl_size,
				   sizeof(struct rx_desc),
				   sizeof(struct rx_sw_desc),
				   &q->fl[0].phys_addr, &q->fl[0].sdesc);
	if (!q->fl[0].desc)
		goto err;

	q->fl[1].desc = alloc_ring(adapter->pdev, p->jumbo_size,
				   sizeof(struct rx_desc),
				   sizeof(struct rx_sw_desc),
				   &q->fl[1].phys_addr, &q->fl[1].sdesc);
	if (!q->fl[1].desc)
		goto err;

	q->rspq.desc = alloc_ring(adapter->pdev, p->rspq_size,
				  sizeof(struct rsp_desc), 0,
				  &q->rspq.phys_addr, NULL);
	if (!q->rspq.desc)
		goto err;

	for (i = 0; i < ntxq; ++i) {
		/*
		 * The control queue always uses immediate data so does not
		 * need to keep track of any sk_buffs.
		 */
		size_t sz = i == TXQ_CTRL ? 0 : sizeof(struct tx_sw_desc);

		q->txq[i].desc = alloc_ring(adapter->pdev, p->txq_size[i],
					    sizeof(struct tx_desc), sz,
					    &q->txq[i].phys_addr,
					    &q->txq[i].sdesc);
		if (!q->txq[i].desc)
			goto err;

		q->txq[i].gen = 1;
		q->txq[i].size = p->txq_size[i];
		spin_lock_init(&q->txq[i].lock);
		skb_queue_head_init(&q->txq[i].sendq);
	}

	tasklet_init(&q->txq[TXQ_OFLD].qresume_tsk, restart_offloadq,
		     (unsigned long)q);
	tasklet_init(&q->txq[TXQ_CTRL].qresume_tsk, restart_ctrlq,
		     (unsigned long)q);

	q->fl[0].gen = q->fl[1].gen = 1;
	q->fl[0].size = p->fl_size;
	q->fl[1].size = p->jumbo_size;

	q->rspq.gen = 1;
	q->rspq.size = p->rspq_size;
	spin_lock_init(&q->rspq.lock);
	skb_queue_head_init(&q->rspq.rx_queue);

	q->txq[TXQ_ETH].stop_thres = nports *
	    flits_to_desc(sgl_len(MAX_SKB_FRAGS + 1) + 3);

#if FL0_PG_CHUNK_SIZE > 0
	q->fl[0].buf_size = FL0_PG_CHUNK_SIZE;
#else
	q->fl[0].buf_size = SGE_RX_SM_BUF_SIZE + sizeof(struct cpl_rx_data);
#endif
#if FL1_PG_CHUNK_SIZE > 0
	q->fl[1].buf_size = FL1_PG_CHUNK_SIZE;
#else
	q->fl[1].buf_size = is_offload(adapter) ?
		(16 * 1024) - SKB_DATA_ALIGN(sizeof(struct skb_shared_info)) :
		MAX_FRAME_SIZE + 2 + sizeof(struct cpl_rx_pkt);
#endif

	q->fl[0].use_pages = FL0_PG_CHUNK_SIZE > 0;
	q->fl[1].use_pages = FL1_PG_CHUNK_SIZE > 0;
	q->fl[0].order = FL0_PG_ORDER;
	q->fl[1].order = FL1_PG_ORDER;
	q->fl[0].alloc_size = FL0_PG_ALLOC_SIZE;
	q->fl[1].alloc_size = FL1_PG_ALLOC_SIZE;

	spin_lock_irq(&adapter->sge.reg_lock);

	/* FL threshold comparison uses < */
	ret = t3_sge_init_rspcntxt(adapter, q->rspq.cntxt_id, irq_vec_idx,
				   q->rspq.phys_addr, q->rspq.size,
				   q->fl[0].buf_size - SGE_PG_RSVD, 1, 0);
	if (ret)
		goto err_unlock;

	for (i = 0; i < SGE_RXQ_PER_SET; ++i) {
		ret = t3_sge_init_flcntxt(adapter, q->fl[i].cntxt_id, 0,
					  q->fl[i].phys_addr, q->fl[i].size,
					  q->fl[i].buf_size - SGE_PG_RSVD,
					  p->cong_thres, 1, 0);
		if (ret)
			goto err_unlock;
	}

	ret = t3_sge_init_ecntxt(adapter, q->txq[TXQ_ETH].cntxt_id, USE_GTS,
				 SGE_CNTXT_ETH, id, q->txq[TXQ_ETH].phys_addr,
				 q->txq[TXQ_ETH].size, q->txq[TXQ_ETH].token,
				 1, 0);
	if (ret)
		goto err_unlock;

	if (ntxq > 1) {
		ret = t3_sge_init_ecntxt(adapter, q->txq[TXQ_OFLD].cntxt_id,
					 USE_GTS, SGE_CNTXT_OFLD, id,
					 q->txq[TXQ_OFLD].phys_addr,
					 q->txq[TXQ_OFLD].size, 0, 1, 0);
		if (ret)
			goto err_unlock;
	}

	if (ntxq > 2) {
		ret = t3_sge_init_ecntxt(adapter, q->txq[TXQ_CTRL].cntxt_id, 0,
					 SGE_CNTXT_CTRL, id,
					 q->txq[TXQ_CTRL].phys_addr,
					 q->txq[TXQ_CTRL].size,
					 q->txq[TXQ_CTRL].token, 1, 0);
		if (ret)
			goto err_unlock;
	}

	spin_unlock_irq(&adapter->sge.reg_lock);

	q->adap = adapter;
	q->netdev = dev;
	q->tx_q = netdevq;
	t3_update_qset_coalesce(q, p);

	avail = refill_fl(adapter, &q->fl[0], q->fl[0].size,
			  GFP_KERNEL | __GFP_COMP);
	if (!avail) {
		CH_ALERT(adapter, "free list queue 0 initialization failed\n");
		goto err;
	}
	if (avail < q->fl[0].size)
		CH_WARN(adapter, "free list queue 0 enabled with %d credits\n",
			avail);

	avail = refill_fl(adapter, &q->fl[1], q->fl[1].size,
			  GFP_KERNEL | __GFP_COMP);
	if (avail < q->fl[1].size)
		CH_WARN(adapter, "free list queue 1 enabled with %d credits\n",
			avail);
	refill_rspq(adapter, &q->rspq, q->rspq.size - 1);

	t3_write_reg(adapter, A_SG_GTS, V_RSPQ(q->rspq.cntxt_id) |
		     V_NEWTIMER(q->rspq.holdoff_tmr));

	return 0;

err_unlock:
	spin_unlock_irq(&adapter->sge.reg_lock);
err:
	t3_free_qset(adapter, q);
	return ret;
}