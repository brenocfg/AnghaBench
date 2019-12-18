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
struct nfp_net_r_vector {TYPE_1__* nfp_net; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  irq_entry; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nfp_ctrl_tx_queued (struct nfp_net_r_vector*) ; 
 scalar_t__ nfp_ctrl_rx (struct nfp_net_r_vector*) ; 
 int /*<<< orphan*/  nfp_net_irq_unmask (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_tx_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_dp_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfp_ctrl_poll(unsigned long arg)
{
	struct nfp_net_r_vector *r_vec = (void *)arg;

	spin_lock(&r_vec->lock);
	nfp_net_tx_complete(r_vec->tx_ring, 0);
	__nfp_ctrl_tx_queued(r_vec);
	spin_unlock(&r_vec->lock);

	if (nfp_ctrl_rx(r_vec)) {
		nfp_net_irq_unmask(r_vec->nfp_net, r_vec->irq_entry);
	} else {
		tasklet_schedule(&r_vec->tasklet);
		nn_dp_warn(&r_vec->nfp_net->dp,
			   "control message budget exceeded!\n");
	}
}