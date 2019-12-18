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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct i40e_ring {scalar_t__ next_to_use; scalar_t__ count; TYPE_1__* vsi; } ;
struct i40e_pf {size_t lan_vsi; TYPE_2__** vsi; } ;
struct i40e_filter_program_desc {void* fd_id; void* dtype_cmd_cntindex; void* rsvd; void* qindex_flex_ptype_vsi; } ;
struct i40e_fdir_filter {int q_index; int flex_off; int pctype; int flex_offset; int dest_ctl; int fd_status; int fd_id; scalar_t__ cnt_index; scalar_t__ dest_vsi; } ;
struct TYPE_4__ {scalar_t__ id; } ;
struct TYPE_3__ {struct i40e_pf* back; } ;

/* Variables and functions */
 int I40E_FILTER_PROGRAM_DESC_PCMD_ADD_UPDATE ; 
 int I40E_FILTER_PROGRAM_DESC_PCMD_REMOVE ; 
 int I40E_TXD_FLTR_QW0_DEST_VSI_MASK ; 
 int I40E_TXD_FLTR_QW0_DEST_VSI_SHIFT ; 
 int I40E_TXD_FLTR_QW0_FLEXOFF_MASK ; 
 int I40E_TXD_FLTR_QW0_FLEXOFF_SHIFT ; 
 int I40E_TXD_FLTR_QW0_PCTYPE_MASK ; 
 int I40E_TXD_FLTR_QW0_PCTYPE_SHIFT ; 
 int I40E_TXD_FLTR_QW0_QINDEX_MASK ; 
 int I40E_TXD_FLTR_QW0_QINDEX_SHIFT ; 
 int I40E_TXD_FLTR_QW1_CNTINDEX_MASK ; 
 int I40E_TXD_FLTR_QW1_CNTINDEX_SHIFT ; 
 int I40E_TXD_FLTR_QW1_CNT_ENA_MASK ; 
 int I40E_TXD_FLTR_QW1_DEST_MASK ; 
 int I40E_TXD_FLTR_QW1_DEST_SHIFT ; 
 int I40E_TXD_FLTR_QW1_FD_STATUS_MASK ; 
 int I40E_TXD_FLTR_QW1_FD_STATUS_SHIFT ; 
 int I40E_TXD_FLTR_QW1_PCMD_SHIFT ; 
 int I40E_TX_DESC_DTYPE_FILTER_PROG ; 
 struct i40e_filter_program_desc* I40E_TX_FDIRDESC (struct i40e_ring*,scalar_t__) ; 
 void* cpu_to_le32 (int) ; 

__attribute__((used)) static void i40e_fdir(struct i40e_ring *tx_ring,
		      struct i40e_fdir_filter *fdata, bool add)
{
	struct i40e_filter_program_desc *fdir_desc;
	struct i40e_pf *pf = tx_ring->vsi->back;
	u32 flex_ptype, dtype_cmd;
	u16 i;

	/* grab the next descriptor */
	i = tx_ring->next_to_use;
	fdir_desc = I40E_TX_FDIRDESC(tx_ring, i);

	i++;
	tx_ring->next_to_use = (i < tx_ring->count) ? i : 0;

	flex_ptype = I40E_TXD_FLTR_QW0_QINDEX_MASK &
		     (fdata->q_index << I40E_TXD_FLTR_QW0_QINDEX_SHIFT);

	flex_ptype |= I40E_TXD_FLTR_QW0_FLEXOFF_MASK &
		      (fdata->flex_off << I40E_TXD_FLTR_QW0_FLEXOFF_SHIFT);

	flex_ptype |= I40E_TXD_FLTR_QW0_PCTYPE_MASK &
		      (fdata->pctype << I40E_TXD_FLTR_QW0_PCTYPE_SHIFT);

	flex_ptype |= I40E_TXD_FLTR_QW0_PCTYPE_MASK &
		      (fdata->flex_offset << I40E_TXD_FLTR_QW0_FLEXOFF_SHIFT);

	/* Use LAN VSI Id if not programmed by user */
	flex_ptype |= I40E_TXD_FLTR_QW0_DEST_VSI_MASK &
		      ((u32)(fdata->dest_vsi ? : pf->vsi[pf->lan_vsi]->id) <<
		       I40E_TXD_FLTR_QW0_DEST_VSI_SHIFT);

	dtype_cmd = I40E_TX_DESC_DTYPE_FILTER_PROG;

	dtype_cmd |= add ?
		     I40E_FILTER_PROGRAM_DESC_PCMD_ADD_UPDATE <<
		     I40E_TXD_FLTR_QW1_PCMD_SHIFT :
		     I40E_FILTER_PROGRAM_DESC_PCMD_REMOVE <<
		     I40E_TXD_FLTR_QW1_PCMD_SHIFT;

	dtype_cmd |= I40E_TXD_FLTR_QW1_DEST_MASK &
		     (fdata->dest_ctl << I40E_TXD_FLTR_QW1_DEST_SHIFT);

	dtype_cmd |= I40E_TXD_FLTR_QW1_FD_STATUS_MASK &
		     (fdata->fd_status << I40E_TXD_FLTR_QW1_FD_STATUS_SHIFT);

	if (fdata->cnt_index) {
		dtype_cmd |= I40E_TXD_FLTR_QW1_CNT_ENA_MASK;
		dtype_cmd |= I40E_TXD_FLTR_QW1_CNTINDEX_MASK &
			     ((u32)fdata->cnt_index <<
			      I40E_TXD_FLTR_QW1_CNTINDEX_SHIFT);
	}

	fdir_desc->qindex_flex_ptype_vsi = cpu_to_le32(flex_ptype);
	fdir_desc->rsvd = cpu_to_le32(0);
	fdir_desc->dtype_cmd_cntindex = cpu_to_le32(dtype_cmd);
	fdir_desc->fd_id = cpu_to_le32(fdata->fd_id);
}