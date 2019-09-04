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
struct nfp_net_r_vector {int /*<<< orphan*/  affinity_mask; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; int /*<<< orphan*/  handler; int /*<<< orphan*/  irq_vector; int /*<<< orphan*/  irq_entry; struct nfp_net* nfp_net; } ;
struct TYPE_2__ {scalar_t__ netdev; } ;
struct nfp_net {int max_r_vecs; TYPE_1__ dp; struct nfp_net_r_vector* r_vecs; struct msix_entry* irq_entries; int /*<<< orphan*/  exn_handler; int /*<<< orphan*/  lsc_handler; } ;
struct msix_entry {int /*<<< orphan*/  vector; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int NFP_NET_NON_Q_VECTORS ; 
 int /*<<< orphan*/  __skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_ctrl_irq_rxtx ; 
 int /*<<< orphan*/  nfp_ctrl_poll ; 
 int /*<<< orphan*/  nfp_net_irq_exn ; 
 int /*<<< orphan*/  nfp_net_irq_lsc ; 
 int /*<<< orphan*/  nfp_net_irq_rxtx ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void nfp_net_vecs_init(struct nfp_net *nn)
{
	struct nfp_net_r_vector *r_vec;
	int r;

	nn->lsc_handler = nfp_net_irq_lsc;
	nn->exn_handler = nfp_net_irq_exn;

	for (r = 0; r < nn->max_r_vecs; r++) {
		struct msix_entry *entry;

		entry = &nn->irq_entries[NFP_NET_NON_Q_VECTORS + r];

		r_vec = &nn->r_vecs[r];
		r_vec->nfp_net = nn;
		r_vec->irq_entry = entry->entry;
		r_vec->irq_vector = entry->vector;

		if (nn->dp.netdev) {
			r_vec->handler = nfp_net_irq_rxtx;
		} else {
			r_vec->handler = nfp_ctrl_irq_rxtx;

			__skb_queue_head_init(&r_vec->queue);
			spin_lock_init(&r_vec->lock);
			tasklet_init(&r_vec->tasklet, nfp_ctrl_poll,
				     (unsigned long)r_vec);
			tasklet_disable(&r_vec->tasklet);
		}

		cpumask_set_cpu(r, &r_vec->affinity_mask);
	}
}