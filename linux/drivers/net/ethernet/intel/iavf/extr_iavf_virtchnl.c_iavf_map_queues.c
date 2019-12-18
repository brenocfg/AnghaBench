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
struct virtchnl_vector_map {scalar_t__ rxq_map; scalar_t__ txq_map; void* vector_id; int /*<<< orphan*/  vsi_id; int /*<<< orphan*/  txitr_idx; int /*<<< orphan*/  rxitr_idx; } ;
struct virtchnl_irq_map_info {void* num_vectors; struct virtchnl_vector_map* vecmap; } ;
struct iavf_q_vector {scalar_t__ ring_mask; } ;
struct iavf_adapter {scalar_t__ current_op; void* num_msix_vectors; int /*<<< orphan*/  aq_required; TYPE_2__* vsi_res; struct iavf_q_vector* q_vectors; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  vsi_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IAVF_FLAG_AQ_MAP_VECTORS ; 
 int /*<<< orphan*/  IAVF_RX_ITR ; 
 int /*<<< orphan*/  IAVF_TX_ITR ; 
 void* NONQ_VECS ; 
 scalar_t__ VIRTCHNL_OP_CONFIG_IRQ_MAP ; 
 scalar_t__ VIRTCHNL_OP_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  iavf_send_pf_msg (struct iavf_adapter*,scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  kfree (struct virtchnl_irq_map_info*) ; 
 struct virtchnl_irq_map_info* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 size_t struct_size (struct virtchnl_irq_map_info*,struct virtchnl_vector_map*,void*) ; 

void iavf_map_queues(struct iavf_adapter *adapter)
{
	struct virtchnl_irq_map_info *vimi;
	struct virtchnl_vector_map *vecmap;
	struct iavf_q_vector *q_vector;
	int v_idx, q_vectors;
	size_t len;

	if (adapter->current_op != VIRTCHNL_OP_UNKNOWN) {
		/* bail because we already have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot map queues to vectors, command %d pending\n",
			adapter->current_op);
		return;
	}
	adapter->current_op = VIRTCHNL_OP_CONFIG_IRQ_MAP;

	q_vectors = adapter->num_msix_vectors - NONQ_VECS;

	len = struct_size(vimi, vecmap, adapter->num_msix_vectors);
	vimi = kzalloc(len, GFP_KERNEL);
	if (!vimi)
		return;

	vimi->num_vectors = adapter->num_msix_vectors;
	/* Queue vectors first */
	for (v_idx = 0; v_idx < q_vectors; v_idx++) {
		q_vector = &adapter->q_vectors[v_idx];
		vecmap = &vimi->vecmap[v_idx];

		vecmap->vsi_id = adapter->vsi_res->vsi_id;
		vecmap->vector_id = v_idx + NONQ_VECS;
		vecmap->txq_map = q_vector->ring_mask;
		vecmap->rxq_map = q_vector->ring_mask;
		vecmap->rxitr_idx = IAVF_RX_ITR;
		vecmap->txitr_idx = IAVF_TX_ITR;
	}
	/* Misc vector last - this is only for AdminQ messages */
	vecmap = &vimi->vecmap[v_idx];
	vecmap->vsi_id = adapter->vsi_res->vsi_id;
	vecmap->vector_id = 0;
	vecmap->txq_map = 0;
	vecmap->rxq_map = 0;

	adapter->aq_required &= ~IAVF_FLAG_AQ_MAP_VECTORS;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_CONFIG_IRQ_MAP,
			 (u8 *)vimi, len);
	kfree(vimi);
}