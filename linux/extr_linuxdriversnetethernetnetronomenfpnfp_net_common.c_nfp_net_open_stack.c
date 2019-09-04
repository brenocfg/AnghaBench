#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int num_r_vecs; int /*<<< orphan*/  netdev; } ;
struct nfp_net {TYPE_1__* irq_entries; TYPE_3__ dp; TYPE_2__* r_vecs; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq_vector; int /*<<< orphan*/  napi; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 size_t NFP_NET_IRQ_LSC_IDX ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_read_link_status (struct nfp_net*) ; 

__attribute__((used)) static void nfp_net_open_stack(struct nfp_net *nn)
{
	unsigned int r;

	for (r = 0; r < nn->dp.num_r_vecs; r++) {
		napi_enable(&nn->r_vecs[r].napi);
		enable_irq(nn->r_vecs[r].irq_vector);
	}

	netif_tx_wake_all_queues(nn->dp.netdev);

	enable_irq(nn->irq_entries[NFP_NET_IRQ_LSC_IDX].vector);
	nfp_net_read_link_status(nn);
}