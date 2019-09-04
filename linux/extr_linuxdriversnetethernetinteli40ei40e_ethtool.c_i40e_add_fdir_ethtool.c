#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
typedef  void* u16 ;
struct i40e_vsi {scalar_t__ num_queue_pairs; void* id; struct i40e_pf* back; } ;
struct i40e_rx_flow_userdef {int /*<<< orphan*/  flex_offset; int /*<<< orphan*/  flex_word; scalar_t__ flex_filter; } ;
struct TYPE_7__ {scalar_t__ fd_filters_best_effort; scalar_t__ fd_filters_guaranteed; } ;
struct TYPE_9__ {int /*<<< orphan*/  pf_id; TYPE_1__ func_caps; } ;
struct i40e_pf {int flags; size_t num_alloc_vfs; int /*<<< orphan*/  fdir_pf_active_filters; TYPE_3__ hw; TYPE_2__* vf; int /*<<< orphan*/  state; } ;
struct i40e_fdir_filter {scalar_t__ fd_id; size_t dest_ctl; int flow_type; int flex_filter; int /*<<< orphan*/  fdir_node; int /*<<< orphan*/  flex_offset; int /*<<< orphan*/  flex_word; int /*<<< orphan*/  src_ip; int /*<<< orphan*/  dst_ip; int /*<<< orphan*/  src_port; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  ip4_proto; int /*<<< orphan*/  cnt_index; int /*<<< orphan*/  fd_status; void* dest_vsi; void* q_index; } ;
struct ethtool_rxnfc {int /*<<< orphan*/  fs; } ;
struct TYPE_11__ {int /*<<< orphan*/  ip4dst; int /*<<< orphan*/  ip4src; int /*<<< orphan*/  pdst; int /*<<< orphan*/  psrc; } ;
struct TYPE_10__ {int /*<<< orphan*/  proto; } ;
struct TYPE_12__ {TYPE_5__ tcp_ip4_spec; TYPE_4__ usr_ip4_spec; } ;
struct ethtool_rx_flow_spec {int flow_type; scalar_t__ location; scalar_t__ ring_cookie; TYPE_6__ h_u; } ;
struct TYPE_8__ {scalar_t__ num_queue_pairs; void* lan_vsi_id; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 int FLOW_EXT ; 
 int FLOW_MAC_EXT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I40E_FD_SB_STAT_IDX (int /*<<< orphan*/ ) ; 
 size_t I40E_FILTER_PROGRAM_DESC_DEST_DIRECT_PACKET_QINDEX ; 
 size_t I40E_FILTER_PROGRAM_DESC_DEST_DROP_PACKET ; 
 int /*<<< orphan*/  I40E_FILTER_PROGRAM_DESC_FD_STATUS_FD_ID ; 
 int I40E_FLAG_FD_SB_ENABLED ; 
 scalar_t__ RX_CLS_FLOW_DISC ; 
 int /*<<< orphan*/  __I40E_FD_FLUSH_REQUESTED ; 
 int /*<<< orphan*/  __I40E_FD_SB_AUTO_DISABLED ; 
 int /*<<< orphan*/  __I40E_RESET_INTR_RECEIVED ; 
 int /*<<< orphan*/  __I40E_RESET_RECOVERY_PENDING ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 scalar_t__ ethtool_get_flow_spec_ring (scalar_t__) ; 
 size_t ethtool_get_flow_spec_ring_vf (scalar_t__) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int i40e_add_del_fdir (struct i40e_vsi*,struct i40e_fdir_filter*,int) ; 
 int i40e_check_fdir_input_set (struct i40e_vsi*,struct ethtool_rx_flow_spec*,struct i40e_rx_flow_userdef*) ; 
 int i40e_disallow_matching_filters (struct i40e_vsi*,struct i40e_fdir_filter*) ; 
 scalar_t__ i40e_parse_rx_flow_user_data (struct ethtool_rx_flow_spec*,struct i40e_rx_flow_userdef*) ; 
 int /*<<< orphan*/  i40e_update_ethtool_fdir_entry (struct i40e_vsi*,struct i40e_fdir_filter*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct i40e_fdir_filter*) ; 
 struct i40e_fdir_filter* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_add_fdir_ethtool(struct i40e_vsi *vsi,
				 struct ethtool_rxnfc *cmd)
{
	struct i40e_rx_flow_userdef userdef;
	struct ethtool_rx_flow_spec *fsp;
	struct i40e_fdir_filter *input;
	u16 dest_vsi = 0, q_index = 0;
	struct i40e_pf *pf;
	int ret = -EINVAL;
	u8 dest_ctl;

	if (!vsi)
		return -EINVAL;
	pf = vsi->back;

	if (!(pf->flags & I40E_FLAG_FD_SB_ENABLED))
		return -EOPNOTSUPP;

	if (test_bit(__I40E_FD_SB_AUTO_DISABLED, pf->state))
		return -ENOSPC;

	if (test_bit(__I40E_RESET_RECOVERY_PENDING, pf->state) ||
	    test_bit(__I40E_RESET_INTR_RECEIVED, pf->state))
		return -EBUSY;

	if (test_bit(__I40E_FD_FLUSH_REQUESTED, pf->state))
		return -EBUSY;

	fsp = (struct ethtool_rx_flow_spec *)&cmd->fs;

	/* Parse the user-defined field */
	if (i40e_parse_rx_flow_user_data(fsp, &userdef))
		return -EINVAL;

	/* Extended MAC field is not supported */
	if (fsp->flow_type & FLOW_MAC_EXT)
		return -EINVAL;

	ret = i40e_check_fdir_input_set(vsi, fsp, &userdef);
	if (ret)
		return ret;

	if (fsp->location >= (pf->hw.func_caps.fd_filters_best_effort +
			      pf->hw.func_caps.fd_filters_guaranteed)) {
		return -EINVAL;
	}

	/* ring_cookie is either the drop index, or is a mask of the queue
	 * index and VF id we wish to target.
	 */
	if (fsp->ring_cookie == RX_CLS_FLOW_DISC) {
		dest_ctl = I40E_FILTER_PROGRAM_DESC_DEST_DROP_PACKET;
	} else {
		u32 ring = ethtool_get_flow_spec_ring(fsp->ring_cookie);
		u8 vf = ethtool_get_flow_spec_ring_vf(fsp->ring_cookie);

		if (!vf) {
			if (ring >= vsi->num_queue_pairs)
				return -EINVAL;
			dest_vsi = vsi->id;
		} else {
			/* VFs are zero-indexed, so we subtract one here */
			vf--;

			if (vf >= pf->num_alloc_vfs)
				return -EINVAL;
			if (ring >= pf->vf[vf].num_queue_pairs)
				return -EINVAL;
			dest_vsi = pf->vf[vf].lan_vsi_id;
		}
		dest_ctl = I40E_FILTER_PROGRAM_DESC_DEST_DIRECT_PACKET_QINDEX;
		q_index = ring;
	}

	input = kzalloc(sizeof(*input), GFP_KERNEL);

	if (!input)
		return -ENOMEM;

	input->fd_id = fsp->location;
	input->q_index = q_index;
	input->dest_vsi = dest_vsi;
	input->dest_ctl = dest_ctl;
	input->fd_status = I40E_FILTER_PROGRAM_DESC_FD_STATUS_FD_ID;
	input->cnt_index  = I40E_FD_SB_STAT_IDX(pf->hw.pf_id);
	input->dst_ip = fsp->h_u.tcp_ip4_spec.ip4src;
	input->src_ip = fsp->h_u.tcp_ip4_spec.ip4dst;
	input->flow_type = fsp->flow_type & ~FLOW_EXT;
	input->ip4_proto = fsp->h_u.usr_ip4_spec.proto;

	/* Reverse the src and dest notion, since the HW expects them to be from
	 * Tx perspective where as the input from user is from Rx filter view.
	 */
	input->dst_port = fsp->h_u.tcp_ip4_spec.psrc;
	input->src_port = fsp->h_u.tcp_ip4_spec.pdst;
	input->dst_ip = fsp->h_u.tcp_ip4_spec.ip4src;
	input->src_ip = fsp->h_u.tcp_ip4_spec.ip4dst;

	if (userdef.flex_filter) {
		input->flex_filter = true;
		input->flex_word = cpu_to_be16(userdef.flex_word);
		input->flex_offset = userdef.flex_offset;
	}

	/* Avoid programming two filters with identical match criteria. */
	ret = i40e_disallow_matching_filters(vsi, input);
	if (ret)
		goto free_filter_memory;

	/* Add the input filter to the fdir_input_list, possibly replacing
	 * a previous filter. Do not free the input structure after adding it
	 * to the list as this would cause a use-after-free bug.
	 */
	i40e_update_ethtool_fdir_entry(vsi, input, fsp->location, NULL);
	ret = i40e_add_del_fdir(vsi, input, true);
	if (ret)
		goto remove_sw_rule;
	return 0;

remove_sw_rule:
	hlist_del(&input->fdir_node);
	pf->fdir_pf_active_filters--;
free_filter_memory:
	kfree(input);
	return ret;
}