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
typedef  int /*<<< orphan*/  u8 ;
struct qede_dev {TYPE_2__* arfs; } ;
struct TYPE_3__ {int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; } ;
struct qede_arfs_fltr_node {scalar_t__ rxq_id; int used; scalar_t__ next_rxq_id; int /*<<< orphan*/  state; scalar_t__ filter_op; TYPE_1__ tuple; int /*<<< orphan*/  sw_id; int /*<<< orphan*/  flow_id; int /*<<< orphan*/  fw_rc; } ;
struct TYPE_4__ {int /*<<< orphan*/  arfs_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  QEDE_FLTR_VALID ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qede_configure_arfs_fltr (struct qede_dev*,struct qede_arfs_fltr_node*,scalar_t__,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void qede_arfs_filter_op(void *dev, void *filter, u8 fw_rc)
{
	struct qede_arfs_fltr_node *fltr = filter;
	struct qede_dev *edev = dev;

	fltr->fw_rc = fw_rc;

	if (fw_rc) {
		DP_NOTICE(edev,
			  "Failed arfs filter configuration fw_rc=%d, flow_id=%d, sw_id=0x%llx, src_port=%d, dst_port=%d, rxq=%d\n",
			  fw_rc, fltr->flow_id, fltr->sw_id,
			  ntohs(fltr->tuple.src_port),
			  ntohs(fltr->tuple.dst_port), fltr->rxq_id);

		spin_lock_bh(&edev->arfs->arfs_list_lock);

		fltr->used = false;
		clear_bit(QEDE_FLTR_VALID, &fltr->state);

		spin_unlock_bh(&edev->arfs->arfs_list_lock);
		return;
	}

	spin_lock_bh(&edev->arfs->arfs_list_lock);

	fltr->used = false;

	if (fltr->filter_op) {
		set_bit(QEDE_FLTR_VALID, &fltr->state);
		if (fltr->rxq_id != fltr->next_rxq_id)
			qede_configure_arfs_fltr(edev, fltr, fltr->rxq_id,
						 false);
	} else {
		clear_bit(QEDE_FLTR_VALID, &fltr->state);
		if (fltr->rxq_id != fltr->next_rxq_id) {
			fltr->rxq_id = fltr->next_rxq_id;
			qede_configure_arfs_fltr(edev, fltr,
						 fltr->rxq_id, true);
		}
	}

	spin_unlock_bh(&edev->arfs->arfs_list_lock);
}