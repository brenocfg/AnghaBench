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
struct nfp_net {int link_up; TYPE_3__ dp; TYPE_1__* r_vecs; TYPE_2__* irq_entries; } ;
struct TYPE_5__ {int /*<<< orphan*/  vector; } ;
struct TYPE_4__ {int /*<<< orphan*/  napi; int /*<<< orphan*/  irq_vector; } ;

/* Variables and functions */
 size_t NFP_NET_IRQ_LSC_IDX ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_net_close_stack(struct nfp_net *nn)
{
	unsigned int r;

	disable_irq(nn->irq_entries[NFP_NET_IRQ_LSC_IDX].vector);
	netif_carrier_off(nn->dp.netdev);
	nn->link_up = false;

	for (r = 0; r < nn->dp.num_r_vecs; r++) {
		disable_irq(nn->r_vecs[r].irq_vector);
		napi_disable(&nn->r_vecs[r].napi);
	}

	netif_tx_disable(nn->dp.netdev);
}