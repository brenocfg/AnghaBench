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
struct TYPE_2__ {int /*<<< orphan*/  rq; int /*<<< orphan*/  xq; int /*<<< orphan*/  dead; } ;
struct ppp {int /*<<< orphan*/  dev; int /*<<< orphan*/  xmit_recursion; int /*<<< orphan*/  xmit_pending; int /*<<< orphan*/ * active_filter; int /*<<< orphan*/ * pass_filter; int /*<<< orphan*/  mrq; TYPE_1__ file; int /*<<< orphan*/ * vj; scalar_t__ n_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_prog_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,struct ppp*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ppp_ccp_closed (struct ppp*) ; 
 int /*<<< orphan*/  ppp_unit_count ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slhc_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ppp_destroy_interface(struct ppp *ppp)
{
	atomic_dec(&ppp_unit_count);

	if (!ppp->file.dead || ppp->n_channels) {
		/* "can't happen" */
		netdev_err(ppp->dev, "ppp: destroying ppp struct %p "
			   "but dead=%d n_channels=%d !\n",
			   ppp, ppp->file.dead, ppp->n_channels);
		return;
	}

	ppp_ccp_closed(ppp);
	if (ppp->vj) {
		slhc_free(ppp->vj);
		ppp->vj = NULL;
	}
	skb_queue_purge(&ppp->file.xq);
	skb_queue_purge(&ppp->file.rq);
#ifdef CONFIG_PPP_MULTILINK
	skb_queue_purge(&ppp->mrq);
#endif /* CONFIG_PPP_MULTILINK */
#ifdef CONFIG_PPP_FILTER
	if (ppp->pass_filter) {
		bpf_prog_destroy(ppp->pass_filter);
		ppp->pass_filter = NULL;
	}

	if (ppp->active_filter) {
		bpf_prog_destroy(ppp->active_filter);
		ppp->active_filter = NULL;
	}
#endif /* CONFIG_PPP_FILTER */

	kfree_skb(ppp->xmit_pending);
	free_percpu(ppp->xmit_recursion);

	free_netdev(ppp->dev);
}