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
struct nfp_net_r_vector {int /*<<< orphan*/  irq_entry; int /*<<< orphan*/  irq_vector; int /*<<< orphan*/  affinity_mask; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  napi; int /*<<< orphan*/  name; int /*<<< orphan*/  handler; } ;
struct TYPE_2__ {scalar_t__ netdev; } ;
struct nfp_net {TYPE_1__ dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_add (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 char* nfp_net_name (struct nfp_net*) ; 
 int /*<<< orphan*/  nfp_net_poll ; 
 int /*<<< orphan*/  nn_dbg (struct nfp_net*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_err (struct nfp_net*,char*,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfp_net_r_vector*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfp_net_prepare_vector(struct nfp_net *nn, struct nfp_net_r_vector *r_vec,
		       int idx)
{
	int err;

	/* Setup NAPI */
	if (nn->dp.netdev)
		netif_napi_add(nn->dp.netdev, &r_vec->napi,
			       nfp_net_poll, NAPI_POLL_WEIGHT);
	else
		tasklet_enable(&r_vec->tasklet);

	snprintf(r_vec->name, sizeof(r_vec->name),
		 "%s-rxtx-%d", nfp_net_name(nn), idx);
	err = request_irq(r_vec->irq_vector, r_vec->handler, 0, r_vec->name,
			  r_vec);
	if (err) {
		if (nn->dp.netdev)
			netif_napi_del(&r_vec->napi);
		else
			tasklet_disable(&r_vec->tasklet);

		nn_err(nn, "Error requesting IRQ %d\n", r_vec->irq_vector);
		return err;
	}
	disable_irq(r_vec->irq_vector);

	irq_set_affinity_hint(r_vec->irq_vector, &r_vec->affinity_mask);

	nn_dbg(nn, "RV%02d: irq=%03d/%03d\n", idx, r_vec->irq_vector,
	       r_vec->irq_entry);

	return 0;
}