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
struct nfp_qdisc {struct nfp_qdisc* children; int /*<<< orphan*/  handle; } ;
struct nfp_port {int /*<<< orphan*/  tc_offload_cnt; } ;
struct nfp_abm_link {int /*<<< orphan*/  qdiscs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_H_MAJ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct nfp_qdisc*) ; 
 int /*<<< orphan*/  nfp_abm_qdisc_clear_mq (struct net_device*,struct nfp_abm_link*,struct nfp_qdisc*) ; 
 struct nfp_port* nfp_port_from_netdev (struct net_device*) ; 
 struct nfp_qdisc* radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfp_abm_qdisc_free(struct net_device *netdev, struct nfp_abm_link *alink,
		   struct nfp_qdisc *qdisc)
{
	struct nfp_port *port = nfp_port_from_netdev(netdev);

	if (!qdisc)
		return;
	nfp_abm_qdisc_clear_mq(netdev, alink, qdisc);
	WARN_ON(radix_tree_delete(&alink->qdiscs,
				  TC_H_MAJ(qdisc->handle)) != qdisc);

	kfree(qdisc->children);
	kfree(qdisc);

	port->tc_offload_cnt--;
}