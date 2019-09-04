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
struct i40iw_qp {int /*<<< orphan*/  ibqp; int /*<<< orphan*/ * cm_node; } ;
struct i40iw_cm_node {struct i40iw_cm_core* cm_core; scalar_t__ qhash_set; int /*<<< orphan*/  iwdev; struct i40iw_qp* iwqp; scalar_t__ apbvt_set; int /*<<< orphan*/  loc_port; TYPE_1__* listener; scalar_t__ close_entry; scalar_t__ accept_pend; int /*<<< orphan*/  accelerated; int /*<<< orphan*/  list; int /*<<< orphan*/  ref_count; } ;
struct i40iw_cm_info {int dummy; } ;
struct i40iw_cm_core {int /*<<< orphan*/  stats_nodes_destroyed; int /*<<< orphan*/  ht_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  pend_accepts_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_MANAGE_APBVT_DEL ; 
 int /*<<< orphan*/  I40IW_QHASH_MANAGE_TYPE_DELETE ; 
 int /*<<< orphan*/  I40IW_QHASH_TYPE_TCP_ESTABLISHED ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_dec_refcnt_listen (struct i40iw_cm_core*,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i40iw_get_addr_info (struct i40iw_cm_node*,struct i40iw_cm_info*) ; 
 int /*<<< orphan*/  i40iw_handle_close_entry (struct i40iw_cm_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_manage_apbvt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_manage_qhash (int /*<<< orphan*/ ,struct i40iw_cm_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i40iw_rem_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct i40iw_cm_node*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void i40iw_rem_ref_cm_node(struct i40iw_cm_node *cm_node)
{
	struct i40iw_cm_core *cm_core = cm_node->cm_core;
	struct i40iw_qp *iwqp;
	struct i40iw_cm_info nfo;
	unsigned long flags;

	spin_lock_irqsave(&cm_node->cm_core->ht_lock, flags);
	if (atomic_dec_return(&cm_node->ref_count)) {
		spin_unlock_irqrestore(&cm_node->cm_core->ht_lock, flags);
		return;
	}
	list_del(&cm_node->list);
	spin_unlock_irqrestore(&cm_node->cm_core->ht_lock, flags);

	/* if the node is destroyed before connection was accelerated */
	if (!cm_node->accelerated && cm_node->accept_pend) {
		pr_err("node destroyed before established\n");
		atomic_dec(&cm_node->listener->pend_accepts_cnt);
	}
	if (cm_node->close_entry)
		i40iw_handle_close_entry(cm_node, 0);
	if (cm_node->listener) {
		i40iw_dec_refcnt_listen(cm_core, cm_node->listener, 0, true);
	} else {
		if (cm_node->apbvt_set) {
			i40iw_manage_apbvt(cm_node->iwdev,
					   cm_node->loc_port,
					   I40IW_MANAGE_APBVT_DEL);
			cm_node->apbvt_set = 0;
		}
		i40iw_get_addr_info(cm_node, &nfo);
		if (cm_node->qhash_set) {
			i40iw_manage_qhash(cm_node->iwdev,
					   &nfo,
					   I40IW_QHASH_TYPE_TCP_ESTABLISHED,
					   I40IW_QHASH_MANAGE_TYPE_DELETE,
					   NULL,
					   false);
			cm_node->qhash_set = 0;
		}
	}

	iwqp = cm_node->iwqp;
	if (iwqp) {
		iwqp->cm_node = NULL;
		i40iw_rem_ref(&iwqp->ibqp);
		cm_node->iwqp = NULL;
	} else if (cm_node->qhash_set) {
		i40iw_get_addr_info(cm_node, &nfo);
		i40iw_manage_qhash(cm_node->iwdev,
				   &nfo,
				   I40IW_QHASH_TYPE_TCP_ESTABLISHED,
				   I40IW_QHASH_MANAGE_TYPE_DELETE,
				   NULL,
				   false);
		cm_node->qhash_set = 0;
	}

	cm_node->cm_core->stats_nodes_destroyed++;
	kfree(cm_node);
}