#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct nfp_qdisc {int type; unsigned int num_children; struct nfp_qdisc* children; void* handle; void* parent_handle; struct net_device* netdev; } ;
struct nfp_port {int /*<<< orphan*/  tc_offload_cnt; } ;
struct nfp_abm_link {TYPE_2__* abm; int /*<<< orphan*/  qdiscs; } ;
struct net_device {int dummy; } ;
typedef  enum nfp_qdisc_type { ____Placeholder_nfp_qdisc_type } nfp_qdisc_type ;
struct TYPE_4__ {TYPE_1__* app; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TC_H_MAJ (void*) ; 
 struct nfp_qdisc* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfp_qdisc*) ; 
 struct nfp_qdisc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_err (int /*<<< orphan*/ ,char*,int) ; 
 struct nfp_port* nfp_port_from_netdev (struct net_device*) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nfp_qdisc*) ; 

__attribute__((used)) static struct nfp_qdisc *
nfp_abm_qdisc_alloc(struct net_device *netdev, struct nfp_abm_link *alink,
		    enum nfp_qdisc_type type, u32 parent_handle, u32 handle,
		    unsigned int children)
{
	struct nfp_port *port = nfp_port_from_netdev(netdev);
	struct nfp_qdisc *qdisc;
	int err;

	qdisc = kzalloc(sizeof(*qdisc), GFP_KERNEL);
	if (!qdisc)
		return NULL;

	if (children) {
		qdisc->children = kcalloc(children, sizeof(void *), GFP_KERNEL);
		if (!qdisc->children)
			goto err_free_qdisc;
	}

	qdisc->netdev = netdev;
	qdisc->type = type;
	qdisc->parent_handle = parent_handle;
	qdisc->handle = handle;
	qdisc->num_children = children;

	err = radix_tree_insert(&alink->qdiscs, TC_H_MAJ(qdisc->handle), qdisc);
	if (err) {
		nfp_err(alink->abm->app->cpp,
			"Qdisc insertion into radix tree failed: %d\n", err);
		goto err_free_child_tbl;
	}

	port->tc_offload_cnt++;
	return qdisc;

err_free_child_tbl:
	kfree(qdisc->children);
err_free_qdisc:
	kfree(qdisc);
	return NULL;
}