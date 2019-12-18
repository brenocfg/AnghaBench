#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nfp_qdisc {int /*<<< orphan*/  num_children; int /*<<< orphan*/  use_cnt; } ;
struct nfp_abm_link {struct nfp_qdisc* root_qdisc; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct nfp_qdisc* nfp_abm_qdisc_find (struct nfp_abm_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_abm_qdisc_free (struct net_device*,struct nfp_abm_link*,struct nfp_qdisc*) ; 
 int /*<<< orphan*/  nfp_abm_qdisc_offload_update (struct nfp_abm_link*) ; 
 int /*<<< orphan*/  nfp_abm_qdisc_unlink_children (struct nfp_qdisc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfp_abm_qdisc_destroy(struct net_device *netdev, struct nfp_abm_link *alink,
		      u32 handle)
{
	struct nfp_qdisc *qdisc;

	qdisc = nfp_abm_qdisc_find(alink, handle);
	if (!qdisc)
		return;

	/* We don't get TC_SETUP_ROOT_QDISC w/ MQ when netdev is unregistered */
	if (alink->root_qdisc == qdisc)
		qdisc->use_cnt--;

	nfp_abm_qdisc_unlink_children(qdisc, 0, qdisc->num_children);
	nfp_abm_qdisc_free(netdev, alink, qdisc);

	if (alink->root_qdisc == qdisc) {
		alink->root_qdisc = NULL;
		/* Only root change matters, other changes are acted upon on
		 * the graft notification.
		 */
		nfp_abm_qdisc_offload_update(alink);
	}
}