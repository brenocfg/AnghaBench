#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct virtnet_info {int max_queue_pairs; TYPE_4__* ctrl; TYPE_4__* sq; TYPE_2__* rq; int /*<<< orphan*/  dev; int /*<<< orphan*/  refill; } ;
struct TYPE_8__ {int /*<<< orphan*/  syncp; } ;
struct TYPE_9__ {TYPE_3__ stats; int /*<<< orphan*/  sg; int /*<<< orphan*/  napi; } ;
struct TYPE_6__ {int /*<<< orphan*/  syncp; } ;
struct TYPE_7__ {TYPE_1__ stats; int /*<<< orphan*/  mrg_avg_pkt_len; int /*<<< orphan*/  sg; int /*<<< orphan*/  napi; int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ewma_pkt_len_init (int /*<<< orphan*/ *) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 
 TYPE_4__* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ napi_tx ; 
 int /*<<< orphan*/  napi_weight ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refill_work ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtnet_poll ; 
 int /*<<< orphan*/  virtnet_poll_tx ; 

__attribute__((used)) static int virtnet_alloc_queues(struct virtnet_info *vi)
{
	int i;

	vi->ctrl = kzalloc(sizeof(*vi->ctrl), GFP_KERNEL);
	if (!vi->ctrl)
		goto err_ctrl;
	vi->sq = kcalloc(vi->max_queue_pairs, sizeof(*vi->sq), GFP_KERNEL);
	if (!vi->sq)
		goto err_sq;
	vi->rq = kcalloc(vi->max_queue_pairs, sizeof(*vi->rq), GFP_KERNEL);
	if (!vi->rq)
		goto err_rq;

	INIT_DELAYED_WORK(&vi->refill, refill_work);
	for (i = 0; i < vi->max_queue_pairs; i++) {
		vi->rq[i].pages = NULL;
		netif_napi_add(vi->dev, &vi->rq[i].napi, virtnet_poll,
			       napi_weight);
		netif_tx_napi_add(vi->dev, &vi->sq[i].napi, virtnet_poll_tx,
				  napi_tx ? napi_weight : 0);

		sg_init_table(vi->rq[i].sg, ARRAY_SIZE(vi->rq[i].sg));
		ewma_pkt_len_init(&vi->rq[i].mrg_avg_pkt_len);
		sg_init_table(vi->sq[i].sg, ARRAY_SIZE(vi->sq[i].sg));

		u64_stats_init(&vi->rq[i].stats.syncp);
		u64_stats_init(&vi->sq[i].stats.syncp);
	}

	return 0;

err_rq:
	kfree(vi->sq);
err_sq:
	kfree(vi->ctrl);
err_ctrl:
	return -ENOMEM;
}