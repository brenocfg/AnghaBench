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
struct nfp_net_r_vector {int /*<<< orphan*/  irq_vector; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  napi; } ;
struct TYPE_2__ {scalar_t__ netdev; } ;
struct nfp_net {TYPE_1__ dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct nfp_net_r_vector*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfp_net_cleanup_vector(struct nfp_net *nn, struct nfp_net_r_vector *r_vec)
{
	irq_set_affinity_hint(r_vec->irq_vector, NULL);
	if (nn->dp.netdev)
		netif_napi_del(&r_vec->napi);
	else
		tasklet_disable(&r_vec->tasklet);

	free_irq(r_vec->irq_vector, r_vec);
}