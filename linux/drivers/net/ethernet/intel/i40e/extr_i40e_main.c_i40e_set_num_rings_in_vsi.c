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
struct i40e_vsi {int type; int alloc_queue_pairs; int num_q_vectors; void* num_rx_desc; void* num_tx_desc; struct i40e_pf* back; } ;
struct i40e_pf {int num_lan_qps; int flags; int num_lan_msix; int num_fdsb_msix; int num_vmdq_qps; int num_vmdq_msix; int num_vf_qps; } ;

/* Variables and functions */
 void* ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENODATA ; 
 int /*<<< orphan*/  I40E_DEFAULT_NUM_DESCRIPTORS ; 
 int /*<<< orphan*/  I40E_FDIR_RING_COUNT ; 
 int I40E_FLAG_MSIX_ENABLED ; 
 int /*<<< orphan*/  I40E_REQ_DESCRIPTOR_MULTIPLE ; 
#define  I40E_VSI_FDIR 131 
#define  I40E_VSI_MAIN 130 
#define  I40E_VSI_SRIOV 129 
#define  I40E_VSI_VMDQ2 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static int i40e_set_num_rings_in_vsi(struct i40e_vsi *vsi)
{
	struct i40e_pf *pf = vsi->back;

	switch (vsi->type) {
	case I40E_VSI_MAIN:
		vsi->alloc_queue_pairs = pf->num_lan_qps;
		if (!vsi->num_tx_desc)
			vsi->num_tx_desc = ALIGN(I40E_DEFAULT_NUM_DESCRIPTORS,
						 I40E_REQ_DESCRIPTOR_MULTIPLE);
		if (!vsi->num_rx_desc)
			vsi->num_rx_desc = ALIGN(I40E_DEFAULT_NUM_DESCRIPTORS,
						 I40E_REQ_DESCRIPTOR_MULTIPLE);
		if (pf->flags & I40E_FLAG_MSIX_ENABLED)
			vsi->num_q_vectors = pf->num_lan_msix;
		else
			vsi->num_q_vectors = 1;

		break;

	case I40E_VSI_FDIR:
		vsi->alloc_queue_pairs = 1;
		vsi->num_tx_desc = ALIGN(I40E_FDIR_RING_COUNT,
					 I40E_REQ_DESCRIPTOR_MULTIPLE);
		vsi->num_rx_desc = ALIGN(I40E_FDIR_RING_COUNT,
					 I40E_REQ_DESCRIPTOR_MULTIPLE);
		vsi->num_q_vectors = pf->num_fdsb_msix;
		break;

	case I40E_VSI_VMDQ2:
		vsi->alloc_queue_pairs = pf->num_vmdq_qps;
		if (!vsi->num_tx_desc)
			vsi->num_tx_desc = ALIGN(I40E_DEFAULT_NUM_DESCRIPTORS,
						 I40E_REQ_DESCRIPTOR_MULTIPLE);
		if (!vsi->num_rx_desc)
			vsi->num_rx_desc = ALIGN(I40E_DEFAULT_NUM_DESCRIPTORS,
						 I40E_REQ_DESCRIPTOR_MULTIPLE);
		vsi->num_q_vectors = pf->num_vmdq_msix;
		break;

	case I40E_VSI_SRIOV:
		vsi->alloc_queue_pairs = pf->num_vf_qps;
		if (!vsi->num_tx_desc)
			vsi->num_tx_desc = ALIGN(I40E_DEFAULT_NUM_DESCRIPTORS,
						 I40E_REQ_DESCRIPTOR_MULTIPLE);
		if (!vsi->num_rx_desc)
			vsi->num_rx_desc = ALIGN(I40E_DEFAULT_NUM_DESCRIPTORS,
						 I40E_REQ_DESCRIPTOR_MULTIPLE);
		break;

	default:
		WARN_ON(1);
		return -ENODATA;
	}

	return 0;
}