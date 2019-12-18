#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qede_dev {TYPE_1__* arfs; } ;
struct qede_arfs_tuple {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* build_hdr ) (TYPE_2__*,void*) ;} ;
struct qede_arfs_fltr_node {int buf_len; int /*<<< orphan*/  rxq_id; void* data; TYPE_2__ tuple; int /*<<< orphan*/  sw_id; } ;
struct ethtool_rx_flow_spec {int /*<<< orphan*/  location; } ;
struct ethtool_rxnfc {struct ethtool_rx_flow_spec fs; } ;
struct TYPE_4__ {int /*<<< orphan*/  arfs_fltr_bmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __qede_lock (struct qede_dev*) ; 
 int /*<<< orphan*/  __qede_unlock (struct qede_dev*) ; 
 int /*<<< orphan*/  kfree (struct qede_arfs_fltr_node*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,struct qede_arfs_tuple*,int) ; 
 int /*<<< orphan*/  qede_configure_arfs_fltr (struct qede_dev*,struct qede_arfs_fltr_node*,int /*<<< orphan*/ ,int) ; 
 int qede_enqueue_fltr_and_config_searcher (struct qede_dev*,struct qede_arfs_fltr_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ qede_flow_find_fltr (struct qede_dev*,struct qede_arfs_tuple*) ; 
 int qede_flow_get_min_header_size (struct qede_arfs_tuple*) ; 
 int /*<<< orphan*/  qede_flow_set_destination (struct qede_dev*,struct qede_arfs_fltr_node*,struct ethtool_rx_flow_spec*) ; 
 int qede_flow_spec_to_rule (struct qede_dev*,struct qede_arfs_tuple*,struct ethtool_rx_flow_spec*) ; 
 int qede_poll_arfs_filter_config (struct qede_dev*,struct qede_arfs_fltr_node*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,void*) ; 

int qede_add_cls_rule(struct qede_dev *edev, struct ethtool_rxnfc *info)
{
	struct ethtool_rx_flow_spec *fsp = &info->fs;
	struct qede_arfs_fltr_node *n;
	struct qede_arfs_tuple t;
	int min_hlen, rc;

	__qede_lock(edev);

	if (!edev->arfs) {
		rc = -EPERM;
		goto unlock;
	}

	/* Translate the flow specification into something fittign our DB */
	rc = qede_flow_spec_to_rule(edev, &t, fsp);
	if (rc)
		goto unlock;

	if (qede_flow_find_fltr(edev, &t)) {
		rc = -EINVAL;
		goto unlock;
	}

	n = kzalloc(sizeof(*n), GFP_KERNEL);
	if (!n) {
		rc = -ENOMEM;
		goto unlock;
	}

	min_hlen = qede_flow_get_min_header_size(&t);
	n->data = kzalloc(min_hlen, GFP_KERNEL);
	if (!n->data) {
		kfree(n);
		rc = -ENOMEM;
		goto unlock;
	}

	n->sw_id = fsp->location;
	set_bit(n->sw_id, edev->arfs->arfs_fltr_bmap);
	n->buf_len = min_hlen;

	memcpy(&n->tuple, &t, sizeof(n->tuple));

	qede_flow_set_destination(edev, n, fsp);

	/* Build a minimal header according to the flow */
	n->tuple.build_hdr(&n->tuple, n->data);

	rc = qede_enqueue_fltr_and_config_searcher(edev, n, 0);
	if (rc)
		goto unlock;

	qede_configure_arfs_fltr(edev, n, n->rxq_id, true);
	rc = qede_poll_arfs_filter_config(edev, n);
unlock:
	__qede_unlock(edev);

	return rc;
}